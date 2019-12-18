#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hio {int hio_cmd; unsigned char* hio_data; size_t hio_length; void* hio_error; scalar_t__ hio_offset; } ;
struct hast_resource {int hr_localflush; int /*<<< orphan*/  hr_localfd; scalar_t__ hr_localoff; int /*<<< orphan*/  hr_stat_activemap_write_error; int /*<<< orphan*/  hr_local_sectorsize; int /*<<< orphan*/  hr_extentsize; scalar_t__ hr_local_mediasize; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 void* EIO ; 
 void* EOPNOTSUPP ; 
#define  HIO_DELETE 131 
#define  HIO_FLUSH 130 
#define  HIO_READ 129 
#define  HIO_WRITE 128 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ METADATA_SIZE ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  QUEUE_INSERT (int /*<<< orphan*/ ,struct hio*) ; 
 int /*<<< orphan*/  QUEUE_TAKE (int /*<<< orphan*/ ,struct hio*) ; 
 size_t activemap_calc_ondisk_size (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* calloc (int,size_t) ; 
 int /*<<< orphan*/  disk ; 
 void* errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ g_delete (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 scalar_t__ g_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,...) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_warning (char*) ; 
 scalar_t__ pread (int /*<<< orphan*/ ,unsigned char*,size_t,scalar_t__) ; 
 scalar_t__ pwrite (int /*<<< orphan*/ ,unsigned char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  reqlog (int /*<<< orphan*/ ,int,int,struct hio*,char*,...) ; 
 int /*<<< orphan*/  send ; 

__attribute__((used)) static void *
disk_thread(void *arg)
{
	struct hast_resource *res = arg;
	struct hio *hio;
	ssize_t ret;
	bool clear_activemap, logerror;

	clear_activemap = true;

	for (;;) {
		pjdlog_debug(2, "disk: Taking request.");
		QUEUE_TAKE(disk, hio);
		while (clear_activemap) {
			unsigned char *map;
			size_t mapsize;

			/*
			 * When first request is received, it means that primary
			 * already received our activemap, merged it and stored
			 * locally. We can now safely clear our activemap.
			 */
			mapsize =
			    activemap_calc_ondisk_size(res->hr_local_mediasize -
			    METADATA_SIZE, res->hr_extentsize,
			    res->hr_local_sectorsize);
			map = calloc(1, mapsize);
			if (map == NULL) {
				pjdlog_warning("Unable to allocate memory to clear local activemap.");
				break;
			}
			if (pwrite(res->hr_localfd, map, mapsize,
			    METADATA_SIZE) != (ssize_t)mapsize) {
				pjdlog_errno(LOG_WARNING,
				    "Unable to store cleared activemap");
				free(map);
				res->hr_stat_activemap_write_error++;
				break;
			}
			free(map);
			clear_activemap = false;
			pjdlog_debug(1, "Local activemap cleared.");
			break;
		}
		reqlog(LOG_DEBUG, 2, -1, hio, "disk: (%p) Got request: ", hio);
		logerror = true;
		/* Handle the actual request. */
		switch (hio->hio_cmd) {
		case HIO_READ:
			ret = pread(res->hr_localfd, hio->hio_data,
			    hio->hio_length,
			    hio->hio_offset + res->hr_localoff);
			if (ret == -1)
				hio->hio_error = errno;
			else if (ret != (int64_t)hio->hio_length)
				hio->hio_error = EIO;
			else
				hio->hio_error = 0;
			break;
		case HIO_WRITE:
			ret = pwrite(res->hr_localfd, hio->hio_data,
			    hio->hio_length,
			    hio->hio_offset + res->hr_localoff);
			if (ret == -1)
				hio->hio_error = errno;
			else if (ret != (int64_t)hio->hio_length)
				hio->hio_error = EIO;
			else
				hio->hio_error = 0;
			break;
		case HIO_DELETE:
			ret = g_delete(res->hr_localfd,
			    hio->hio_offset + res->hr_localoff,
			    hio->hio_length);
			if (ret == -1)
				hio->hio_error = errno;
			else
				hio->hio_error = 0;
			break;
		case HIO_FLUSH:
			if (!res->hr_localflush) {
				ret = -1;
				hio->hio_error = EOPNOTSUPP;
				logerror = false;
				break;
			}
			ret = g_flush(res->hr_localfd);
			if (ret == -1) {
				if (errno == EOPNOTSUPP)
					res->hr_localflush = false;
				hio->hio_error = errno;
			} else {
				hio->hio_error = 0;
			}
			break;
		default:
			PJDLOG_ABORT("Unexpected command (cmd=%hhu).",
			    hio->hio_cmd);
		}
		if (logerror && hio->hio_error != 0) {
			reqlog(LOG_ERR, 0, hio->hio_error, hio,
			    "Request failed: ");
		}
		pjdlog_debug(2, "disk: (%p) Moving request to the send queue.",
		    hio);
		QUEUE_INSERT(send, hio);
	}
	/* NOTREACHED */
	return (NULL);
}