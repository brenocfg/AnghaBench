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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
#define  NV_TYPE_BINARY 139 
#define  NV_TYPE_BOOL 138 
#define  NV_TYPE_BOOL_ARRAY 137 
#define  NV_TYPE_DESCRIPTOR 136 
#define  NV_TYPE_DESCRIPTOR_ARRAY 135 
#define  NV_TYPE_NULL 134 
#define  NV_TYPE_NUMBER 133 
#define  NV_TYPE_NUMBER_ARRAY 132 
#define  NV_TYPE_NVLIST 131 
#define  NV_TYPE_NVLIST_ARRAY 130 
#define  NV_TYPE_STRING 129 
#define  NV_TYPE_STRING_ARRAY 128 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  dprintf (int,char*,...) ; 
 scalar_t__ nvlist_dump_error_check (int /*<<< orphan*/  const* const,int,int) ; 
 int /*<<< orphan*/ * nvlist_first_nvpair (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * nvlist_get_pararr (int /*<<< orphan*/  const*,void**) ; 
 scalar_t__ nvlist_in_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 unsigned char* nvpair_get_binary (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_bool (int /*<<< orphan*/ *) ; 
 int* nvpair_get_bool_array (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_descriptor (int /*<<< orphan*/ *) ; 
 int* nvpair_get_descriptor_array (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_get_number_array (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * nvpair_get_nvlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** nvpair_get_nvlist_array (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_string (int /*<<< orphan*/ *) ; 
 char** nvpair_get_string_array (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_type_string (int) ; 

void
nvlist_dump(const nvlist_t *nvl, int fd)
{
	const nvlist_t *tmpnvl;
	nvpair_t *nvp, *tmpnvp;
	void *cookie;
	int level;

	level = 0;
	if (nvlist_dump_error_check(nvl, fd, level))
		return;

	nvp = nvlist_first_nvpair(nvl);
	while (nvp != NULL) {
		dprintf(fd, "%*s%s (%s):", level * 4, "", nvpair_name(nvp),
		    nvpair_type_string(nvpair_type(nvp)));
		switch (nvpair_type(nvp)) {
		case NV_TYPE_NULL:
			dprintf(fd, " null\n");
			break;
		case NV_TYPE_BOOL:
			dprintf(fd, " %s\n", nvpair_get_bool(nvp) ?
			    "TRUE" : "FALSE");
			break;
		case NV_TYPE_NUMBER:
			dprintf(fd, " %ju (%jd) (0x%jx)\n",
			    (uintmax_t)nvpair_get_number(nvp),
			    (intmax_t)nvpair_get_number(nvp),
			    (uintmax_t)nvpair_get_number(nvp));
			break;
		case NV_TYPE_STRING:
			dprintf(fd, " [%s]\n", nvpair_get_string(nvp));
			break;
		case NV_TYPE_NVLIST:
			dprintf(fd, "\n");
			tmpnvl = nvpair_get_nvlist(nvp);
			if (nvlist_dump_error_check(tmpnvl, fd, level + 1))
				break;
			tmpnvp = nvlist_first_nvpair(tmpnvl);
			if (tmpnvp != NULL) {
				nvl = tmpnvl;
				nvp = tmpnvp;
				level++;
				continue;
			}
			break;
		case NV_TYPE_DESCRIPTOR:
			dprintf(fd, " %d\n", nvpair_get_descriptor(nvp));
			break;
		case NV_TYPE_BINARY:
		    {
			const unsigned char *binary;
			unsigned int ii;
			size_t size;

			binary = nvpair_get_binary(nvp, &size);
			dprintf(fd, " %zu ", size);
			for (ii = 0; ii < size; ii++)
				dprintf(fd, "%02hhx", binary[ii]);
			dprintf(fd, "\n");
			break;
		    }
		case NV_TYPE_BOOL_ARRAY:
		    {
			const bool *value;
			unsigned int ii;
			size_t nitems;

			value = nvpair_get_bool_array(nvp, &nitems);
			dprintf(fd, " [ ");
			for (ii = 0; ii < nitems; ii++) {
				dprintf(fd, "%s", value[ii] ? "TRUE" : "FALSE");
				if (ii != nitems - 1)
					dprintf(fd, ", ");
			}
			dprintf(fd, " ]\n");
			break;
		    }
		case NV_TYPE_STRING_ARRAY:
		    {
			const char * const *value;
			unsigned int ii;
			size_t nitems;

			value = nvpair_get_string_array(nvp, &nitems);
			dprintf(fd, " [ ");
			for (ii = 0; ii < nitems; ii++) {
				if (value[ii] == NULL)
					dprintf(fd, "NULL");
				else
					dprintf(fd, "\"%s\"", value[ii]);
				if (ii != nitems - 1)
					dprintf(fd, ", ");
			}
			dprintf(fd, " ]\n");
			break;
		    }
		case NV_TYPE_NUMBER_ARRAY:
		    {
			const uint64_t *value;
			unsigned int ii;
			size_t nitems;

			value = nvpair_get_number_array(nvp, &nitems);
			dprintf(fd, " [ ");
			for (ii = 0; ii < nitems; ii++) {
				dprintf(fd, "%ju (%jd) (0x%jx)",
				    value[ii], value[ii], value[ii]);
				if (ii != nitems - 1)
					dprintf(fd, ", ");
			}
			dprintf(fd, " ]\n");
			break;
		    }
		case NV_TYPE_DESCRIPTOR_ARRAY:
		    {
			const int *value;
			unsigned int ii;
			size_t nitems;

			value = nvpair_get_descriptor_array(nvp, &nitems);
			dprintf(fd, " [ ");
			for (ii = 0; ii < nitems; ii++) {
				dprintf(fd, "%d", value[ii]);
				if (ii != nitems - 1)
					dprintf(fd, ", ");
			}
			dprintf(fd, " ]\n");
			break;
		    }
		case NV_TYPE_NVLIST_ARRAY:
		    {
			const nvlist_t * const *value;
			unsigned int ii;
			size_t nitems;

			value = nvpair_get_nvlist_array(nvp, &nitems);
			dprintf(fd, " %zu\n", nitems);
			tmpnvl = NULL;
			tmpnvp = NULL;
			for (ii = 0; ii < nitems; ii++) {
				if (nvlist_dump_error_check(value[ii], fd,
				    level + 1)) {
					break;
				}

				if (tmpnvl == NULL) {
					tmpnvp = nvlist_first_nvpair(value[ii]);
					if (tmpnvp != NULL) {
						tmpnvl = value[ii];
					} else {
						dprintf(fd, "%*s,\n",
						    (level + 1) * 4, "");
					}
				}
			}
			if (tmpnvp != NULL) {
				nvl = tmpnvl;
				nvp = tmpnvp;
				level++;
				continue;
			}
			break;
		    }
		default:
			PJDLOG_ABORT("Unknown type: %d.", nvpair_type(nvp));
		}

		while ((nvp = nvlist_next_nvpair(nvl, nvp)) == NULL) {
			do {
				cookie = NULL;
				if (nvlist_in_array(nvl))
					dprintf(fd, "%*s,\n", level * 4, "");
				nvl = nvlist_get_pararr(nvl, &cookie);
				if (nvl == NULL)
					return;
				if (nvlist_in_array(nvl) && cookie == NULL) {
					nvp = nvlist_first_nvpair(nvl);
				} else {
					nvp = cookie;
					level--;
				}
			} while (nvp == NULL);
			if (nvlist_in_array(nvl) && cookie == NULL)
				break;
		}
	}
}