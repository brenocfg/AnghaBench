#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long uint8_t ;
typedef  size_t u_int ;
struct mfi_query_disk {int /*<<< orphan*/  devname; } ;
struct mfi_ld_list {size_t ld_count; TYPE_3__* ld_list; } ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_4__ {long target_id; } ;
struct TYPE_5__ {TYPE_1__ v; } ;
struct TYPE_6__ {TYPE_2__ ld; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MFI_DCMD_LD_GET_LIST ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_ld_list*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_query_disk (int,long,struct mfi_query_disk*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int
mfi_lookup_volume(int fd, const char *name, uint8_t *target_id)
{
	struct mfi_query_disk info;
	struct mfi_ld_list list;
	char *cp;
	long val;
	u_int i;

	/* If it's a valid number, treat it as a raw target ID. */
	val = strtol(name, &cp, 0);
	if (*cp == '\0') {
		*target_id = val;
		return (0);
	}

	if (mfi_dcmd_command(fd, MFI_DCMD_LD_GET_LIST, &list, sizeof(list),
	    NULL, 0, NULL) < 0)
		return (-1);	

	for (i = 0; i < list.ld_count; i++) {
		if (mfi_query_disk(fd, list.ld_list[i].ld.v.target_id,
		    &info) < 0)
			continue;
		if (strcmp(name, info.devname) == 0) {
			*target_id = list.ld_list[i].ld.v.target_id;
			return (0);
		}
	}
	errno = EINVAL;
	return (-1);
}