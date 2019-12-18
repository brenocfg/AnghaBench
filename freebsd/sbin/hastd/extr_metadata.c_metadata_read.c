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
struct nv {int dummy; } ;
struct hast_resource {int hr_localfd; char* hr_name; int hr_extentsize; int hr_keepdirty; scalar_t__ hr_role; int /*<<< orphan*/  hr_localpath; scalar_t__ hr_previous_role; void* hr_primary_remotecnt; void* hr_primary_localcnt; void* hr_secondary_remotecnt; void* hr_secondary_localcnt; void* hr_resuid; void* hr_localoff; void* hr_datasize; } ;
struct ebuf {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ HAST_ROLE_PRIMARY ; 
 scalar_t__ HAST_ROLE_SECONDARY ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int METADATA_SIZE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int ebuf_add_tail (struct ebuf*,int /*<<< orphan*/ *,int) ; 
 struct ebuf* ebuf_alloc (int) ; 
 unsigned char* ebuf_data (struct ebuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ebuf_free (struct ebuf*) ; 
 int errno ; 
 int flock (int,int) ; 
 scalar_t__ nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 char* nv_get_string (struct nv*,char*) ; 
 scalar_t__ nv_get_uint32 (struct nv*,char*) ; 
 void* nv_get_uint64 (struct nv*,char*) ; 
 struct nv* nv_ntoh (struct ebuf*) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pjdlog_error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_warning (char*,int /*<<< orphan*/ ) ; 
 int pread (int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int provinfo (struct hast_resource*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
metadata_read(struct hast_resource *res, bool openrw)
{
	unsigned char *buf;
	struct ebuf *eb;
	struct nv *nv;
	ssize_t done;
	const char *str;
	int rerrno;
	bool opened_here;

	opened_here = false;
	rerrno = 0;

	/*
	 * Is this first metadata_read() call for this resource?
	 */
	if (res->hr_localfd == -1) {
		if (provinfo(res, openrw) == -1) {
			rerrno = errno;
			goto fail;
		}
		opened_here = true;
		pjdlog_debug(1, "Obtained info about %s.", res->hr_localpath);
		if (openrw) {
			if (flock(res->hr_localfd, LOCK_EX | LOCK_NB) == -1) {
				rerrno = errno;
				if (errno == EOPNOTSUPP) {
					pjdlog_warning("Unable to lock %s (operation not supported), but continuing.",
					    res->hr_localpath);
				} else {
					pjdlog_errno(LOG_ERR,
					    "Unable to lock %s",
					    res->hr_localpath);
					goto fail;
				}
			}
			pjdlog_debug(1, "Locked %s.", res->hr_localpath);
		}
	}

	eb = ebuf_alloc(METADATA_SIZE);
	if (eb == NULL) {
		rerrno = errno;
		pjdlog_errno(LOG_ERR,
		    "Unable to allocate memory to read metadata");
		goto fail;
	}
	if (ebuf_add_tail(eb, NULL, METADATA_SIZE) == -1) {
		rerrno = errno;
		pjdlog_errno(LOG_ERR,
		    "Unable to allocate memory to read metadata");
		ebuf_free(eb);
		goto fail;
	}
	buf = ebuf_data(eb, NULL);
	PJDLOG_ASSERT(buf != NULL);
	done = pread(res->hr_localfd, buf, METADATA_SIZE, 0);
	if (done == -1 || done != METADATA_SIZE) {
		rerrno = errno;
		pjdlog_errno(LOG_ERR, "Unable to read metadata");
		ebuf_free(eb);
		goto fail;
	}
	nv = nv_ntoh(eb);
	if (nv == NULL) {
		rerrno = errno;
		pjdlog_errno(LOG_ERR, "Metadata read from %s is invalid",
		    res->hr_localpath);
		ebuf_free(eb);
		goto fail;
	}

	str = nv_get_string(nv, "resource");
	if (str != NULL && strcmp(str, res->hr_name) != 0) {
		pjdlog_error("Provider %s is not part of resource %s.",
		    res->hr_localpath, res->hr_name);
		nv_free(nv);
		goto fail;
	}

	res->hr_datasize = nv_get_uint64(nv, "datasize");
	res->hr_extentsize = (int)nv_get_uint32(nv, "extentsize");
	res->hr_keepdirty = (int)nv_get_uint32(nv, "keepdirty");
	res->hr_localoff = nv_get_uint64(nv, "offset");
	res->hr_resuid = nv_get_uint64(nv, "resuid");
	if (res->hr_role != HAST_ROLE_PRIMARY) {
		/* Secondary or init role. */
		res->hr_secondary_localcnt = nv_get_uint64(nv, "localcnt");
		res->hr_secondary_remotecnt = nv_get_uint64(nv, "remotecnt");
	}
	if (res->hr_role != HAST_ROLE_SECONDARY) {
		/* Primary or init role. */
		res->hr_primary_localcnt = nv_get_uint64(nv, "localcnt");
		res->hr_primary_remotecnt = nv_get_uint64(nv, "remotecnt");
	}
	str = nv_get_string(nv, "prevrole");
	if (str != NULL) {
		if (strcmp(str, "primary") == 0)
			res->hr_previous_role = HAST_ROLE_PRIMARY;
		else if (strcmp(str, "secondary") == 0)
			res->hr_previous_role = HAST_ROLE_SECONDARY;
	}

	if (nv_error(nv) != 0) {
		errno = rerrno = nv_error(nv);
		pjdlog_errno(LOG_ERR, "Unable to read metadata from %s",
		    res->hr_localpath);
		nv_free(nv);
		goto fail;
	}
	nv_free(nv);
	return (0);
fail:
	if (opened_here) {
		close(res->hr_localfd);
		res->hr_localfd = -1;
	}
	errno = rerrno;
	return (-1);
}