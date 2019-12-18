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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nv {int dummy; } ;
struct hast_resource {scalar_t__ hr_role; scalar_t__ hr_previous_role; int /*<<< orphan*/  hr_localfd; int /*<<< orphan*/  hr_secondary_remotecnt; int /*<<< orphan*/  hr_secondary_localcnt; int /*<<< orphan*/  hr_primary_remotecnt; int /*<<< orphan*/  hr_primary_localcnt; int /*<<< orphan*/  hr_resuid; scalar_t__ hr_localoff; scalar_t__ hr_keepdirty; scalar_t__ hr_extentsize; scalar_t__ hr_datasize; int /*<<< orphan*/  hr_name; } ;
struct ebuf {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ HAST_ROLE_INIT ; 
 scalar_t__ HAST_ROLE_PRIMARY ; 
 scalar_t__ HAST_ROLE_SECONDARY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 size_t METADATA_SIZE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  bcopy (unsigned char*,unsigned char*,size_t) ; 
 unsigned char* calloc (int,size_t) ; 
 unsigned char* ebuf_data (struct ebuf*,size_t*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  nv_add_string (struct nv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nv_add_uint32 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nv_add_uint64 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 struct nv* nv_alloc () ; 
 scalar_t__ nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 struct ebuf* nv_hton (struct nv*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_error (char*,...) ; 
 int pwrite (int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  role2str (scalar_t__) ; 

int
metadata_write(struct hast_resource *res)
{
	struct ebuf *eb;
	struct nv *nv;
	unsigned char *buf, *ptr;
	size_t size;
	ssize_t done;
	int ret;

	buf = calloc(1, METADATA_SIZE);
	if (buf == NULL) {
		pjdlog_error("Unable to allocate %zu bytes for metadata.",
		    (size_t)METADATA_SIZE);
		return (-1);
	}

	ret = -1;

	nv = nv_alloc();
	nv_add_string(nv, res->hr_name, "resource");
	nv_add_uint64(nv, (uint64_t)res->hr_datasize, "datasize");
	nv_add_uint32(nv, (uint32_t)res->hr_extentsize, "extentsize");
	nv_add_uint32(nv, (uint32_t)res->hr_keepdirty, "keepdirty");
	nv_add_uint64(nv, (uint64_t)res->hr_localoff, "offset");
	nv_add_uint64(nv, res->hr_resuid, "resuid");
	if (res->hr_role == HAST_ROLE_PRIMARY ||
	    res->hr_role == HAST_ROLE_INIT) {
		nv_add_uint64(nv, res->hr_primary_localcnt, "localcnt");
		nv_add_uint64(nv, res->hr_primary_remotecnt, "remotecnt");
	} else /* if (res->hr_role == HAST_ROLE_SECONDARY) */ {
		PJDLOG_ASSERT(res->hr_role == HAST_ROLE_SECONDARY);
		nv_add_uint64(nv, res->hr_secondary_localcnt, "localcnt");
		nv_add_uint64(nv, res->hr_secondary_remotecnt, "remotecnt");
	}
	nv_add_string(nv, role2str(res->hr_role), "prevrole");
	if (nv_error(nv) != 0) {
		pjdlog_error("Unable to create metadata.");
		goto end;
	}
	res->hr_previous_role = res->hr_role;
	eb = nv_hton(nv);
	PJDLOG_ASSERT(eb != NULL);
	ptr = ebuf_data(eb, &size);
	PJDLOG_ASSERT(ptr != NULL);
	PJDLOG_ASSERT(size < METADATA_SIZE);
	bcopy(ptr, buf, size);
	done = pwrite(res->hr_localfd, buf, METADATA_SIZE, 0);
	if (done == -1 || done != METADATA_SIZE) {
		pjdlog_errno(LOG_ERR, "Unable to write metadata");
		goto end;
	}
	ret = 0;
end:
	free(buf);
	nv_free(nv);
	return (ret);
}