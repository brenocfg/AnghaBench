#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct statfs {int /*<<< orphan*/  f_fstypename; } ;
struct asn_oid {int dummy; } ;
struct TYPE_2__ {struct asn_oid const* oid; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 size_t N_FS_TYPE_MAP ; 
 struct asn_oid const OIDX_hrFSUnknown_c ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* fs_type_map ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const struct asn_oid *
fs_get_type(const struct statfs *fs_p)
{
	u_int t;

	assert(fs_p != NULL);

	for (t = 0; t < N_FS_TYPE_MAP; t++)
		if (strcmp(fs_type_map[t].str, fs_p->f_fstypename) == 0)
			return (fs_type_map[t].oid);

	return (&OIDX_hrFSUnknown_c);
}