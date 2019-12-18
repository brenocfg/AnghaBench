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
 int CAP_SYSCTL_RDWR ; 
 int CAP_SYSCTL_RECURSIVE ; 
 int EINVAL ; 
 unsigned int HAS_ID ; 
 unsigned int HAS_MIB ; 
 unsigned int HAS_NAME ; 
 unsigned int HAS_OPERATION ; 
 int NV_TYPE_BINARY ; 
 int NV_TYPE_NUMBER ; 
 int NV_TYPE_STRING ; 
 int /*<<< orphan*/  cnvlist_get_binary (void*,size_t*) ; 
 int cnvlist_get_number (void*) ; 
 int nvlist_error (int /*<<< orphan*/  const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
sysctl_valid(const nvlist_t *nvl, bool limit)
{
	const char *name;
	void *cookie;
	int type;
	size_t size;
	unsigned int field, fields;

	/* NULL nvl is of course invalid. */
	if (nvl == NULL)
		return (EINVAL);
	if (nvlist_error(nvl) != 0)
		return (nvlist_error(nvl));

#define	HAS_NAME	0x01
#define	HAS_MIB		0x02
#define	HAS_ID		(HAS_NAME | HAS_MIB)
#define	HAS_OPERATION	0x04

	fields = 0;
	cookie = NULL;
	while ((name = nvlist_next(nvl, &type, &cookie)) != NULL) {
		if ((strcmp(name, "name") == 0 && type == NV_TYPE_STRING) ||
		    (strcmp(name, "mib") == 0 && type == NV_TYPE_BINARY)) {
			if (strcmp(name, "mib") == 0) {
				/* A MIB must be an array of integers. */
				(void)cnvlist_get_binary(cookie, &size);
				if (size % sizeof(int) != 0)
					return (EINVAL);
				field = HAS_MIB;
			} else
				field = HAS_NAME;

			/*
			 * A limit may contain both a name and a MIB identifier.
			 */
			if ((fields & field) != 0 ||
			    (!limit && (fields & HAS_ID) != 0))
				return (EINVAL);
			fields |= field;
		} else if (strcmp(name, "operation") == 0) {
			uint64_t mask, operation;

			if (type != NV_TYPE_NUMBER)
				return (EINVAL);

			operation = cnvlist_get_number(cookie);

			/*
			 * Requests can only include the RDWR flags; limits may
			 * also include the RECURSIVE flag.
			 */
			mask = limit ? (CAP_SYSCTL_RDWR |
			    CAP_SYSCTL_RECURSIVE) : CAP_SYSCTL_RDWR;
			if ((operation & ~mask) != 0 ||
			    (operation & CAP_SYSCTL_RDWR) == 0)
				return (EINVAL);
			/* Only one 'operation' can be present. */
			if ((fields & HAS_OPERATION) != 0)
				return (EINVAL);
			fields |= HAS_OPERATION;
		} else if (limit)
			return (EINVAL);
	}

	if ((fields & HAS_OPERATION) == 0 || (fields & HAS_ID) == 0)
		return (EINVAL);

#undef HAS_OPERATION
#undef HAS_ID
#undef HAS_MIB
#undef HAS_NAME

	return (0);
}