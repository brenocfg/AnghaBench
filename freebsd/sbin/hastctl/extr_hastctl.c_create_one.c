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
struct hast_resource {char* hr_name; scalar_t__ hr_local_mediasize; size_t hr_localpath; scalar_t__ hr_local_sectorsize; scalar_t__ hr_localfd; scalar_t__ hr_localoff; scalar_t__ hr_keepdirty; scalar_t__ hr_extentsize; scalar_t__ hr_datasize; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int EX_DATAERR ; 
 int EX_IOERR ; 
 int EX_NOINPUT ; 
 int EX_TEMPFAIL ; 
 scalar_t__ HAST_EXTENTSIZE ; 
 scalar_t__ HAST_KEEPDIRTY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ METADATA_SIZE ; 
 size_t activemap_calc_ondisk_size (scalar_t__,scalar_t__,scalar_t__) ; 
 unsigned char* calloc (int,size_t) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int metadata_write (struct hast_resource*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  pjdlog_error (char*,size_t,...) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*,char*) ; 
 int /*<<< orphan*/  powerof2 (scalar_t__) ; 
 int provinfo (struct hast_resource*,int) ; 
 scalar_t__ pwrite (scalar_t__,unsigned char*,size_t,scalar_t__) ; 

__attribute__((used)) static int
create_one(struct hast_resource *res, intmax_t mediasize, intmax_t extentsize,
    intmax_t keepdirty)
{
	unsigned char *buf;
	size_t mapsize;
	int ec;

	ec = 0;
	pjdlog_prefix_set("[%s] ", res->hr_name);

	if (provinfo(res, true) == -1) {
		ec = EX_NOINPUT;
		goto end;
	}
	if (mediasize == 0)
		mediasize = res->hr_local_mediasize;
	else if (mediasize > res->hr_local_mediasize) {
		pjdlog_error("Provided mediasize is larger than provider %s size.",
		    res->hr_localpath);
		ec = EX_DATAERR;
		goto end;
	}
	if (!powerof2(res->hr_local_sectorsize)) {
		pjdlog_error("Sector size of provider %s is not power of 2 (%u).",
		    res->hr_localpath, res->hr_local_sectorsize);
		ec = EX_DATAERR;
		goto end;
	}
	if (extentsize == 0)
		extentsize = HAST_EXTENTSIZE;
	if (extentsize < res->hr_local_sectorsize) {
		pjdlog_error("Extent size (%jd) is less than sector size (%u).",
		    (intmax_t)extentsize, res->hr_local_sectorsize);
		ec = EX_DATAERR;
		goto end;
	}
	if ((extentsize % res->hr_local_sectorsize) != 0) {
		pjdlog_error("Extent size (%jd) is not multiple of sector size (%u).",
		    (intmax_t)extentsize, res->hr_local_sectorsize);
		ec = EX_DATAERR;
		goto end;
	}
	mapsize = activemap_calc_ondisk_size(mediasize - METADATA_SIZE,
	    extentsize, res->hr_local_sectorsize);
	if (keepdirty == 0)
		keepdirty = HAST_KEEPDIRTY;
	res->hr_datasize = mediasize - METADATA_SIZE - mapsize;
	res->hr_extentsize = extentsize;
	res->hr_keepdirty = keepdirty;

	res->hr_localoff = METADATA_SIZE + mapsize;

	if (metadata_write(res) == -1) {
		ec = EX_IOERR;
		goto end;
	}
	buf = calloc(1, mapsize);
	if (buf == NULL) {
		pjdlog_error("Unable to allocate %zu bytes of memory for initial bitmap.",
		    mapsize);
		ec = EX_TEMPFAIL;
		goto end;
	}
	if (pwrite(res->hr_localfd, buf, mapsize, METADATA_SIZE) !=
	    (ssize_t)mapsize) {
		pjdlog_errno(LOG_ERR, "Unable to store initial bitmap on %s",
		    res->hr_localpath);
		free(buf);
		ec = EX_IOERR;
		goto end;
	}
	free(buf);
end:
	if (res->hr_localfd >= 0)
		close(res->hr_localfd);
	pjdlog_prefix_set("%s", "");
	return (ec);
}