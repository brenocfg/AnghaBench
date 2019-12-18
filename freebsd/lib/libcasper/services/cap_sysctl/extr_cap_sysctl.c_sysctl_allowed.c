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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int CAP_SYSCTL_RECURSIVE ; 
 int NV_TYPE_NVLIST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * cnvlist_get_nvlist (void*) ; 
 int* dnvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* dnvlist_get_string (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int const*,int const*,size_t) ; 
 int nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static bool
sysctl_allowed(const nvlist_t *limits, const nvlist_t *req)
{
	const nvlist_t *limit;
	uint64_t op, reqop;
	const char *lname, *name, *reqname;
	void *cookie;
	size_t lsize, reqsize;
	const int *lmib, *reqmib;
	int type;

	if (limits == NULL)
		return (true);

	reqmib = dnvlist_get_binary(req, "mib", &reqsize, NULL, 0);
	reqname = dnvlist_get_string(req, "name", NULL);
	reqop = nvlist_get_number(req, "operation");

	cookie = NULL;
	while ((name = nvlist_next(limits, &type, &cookie)) != NULL) {
		assert(type == NV_TYPE_NVLIST);

		limit = cnvlist_get_nvlist(cookie);
		op = nvlist_get_number(limit, "operation");
		if ((reqop & op) != reqop)
			continue;

		if (reqname != NULL) {
			lname = dnvlist_get_string(limit, "name", NULL);
			if (lname == NULL)
				continue;
			if ((op & CAP_SYSCTL_RECURSIVE) == 0) {
				if (strcmp(lname, reqname) != 0)
					continue;
			} else {
				size_t namelen;

				namelen = strlen(lname);
				if (strncmp(lname, reqname, namelen) != 0)
					continue;
				if (reqname[namelen] != '.' &&
				    reqname[namelen] != '\0')
					continue;
			}
		} else {
			lmib = dnvlist_get_binary(limit, "mib", &lsize, NULL, 0);
			if (lmib == NULL)
				continue;
			if (lsize > reqsize || ((op & CAP_SYSCTL_RECURSIVE) == 0 &&
			    lsize < reqsize))
				continue;
			if (memcmp(lmib, reqmib, lsize) != 0)
				continue;
		}

		return (true);
	}

	return (false);
}