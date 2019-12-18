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
struct dn_fsk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fshash; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNHT_REMOVE ; 
 int /*<<< orphan*/  DN_BH_WLOCK () ; 
 int /*<<< orphan*/  DN_BH_WUNLOCK () ; 
 int DN_DELETE_FS ; 
 int DN_DETACH ; 
 int EINVAL ; 
 int /*<<< orphan*/  ND (char*,int,struct dn_fsk*) ; 
 TYPE_1__ dn_cfg ; 
 struct dn_fsk* dn_ht_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsk_detach (struct dn_fsk*,int) ; 

__attribute__((used)) static int
delete_fs(int i, int locked)
{
	struct dn_fsk *fs;
	int err = 0;

	if (!locked)
		DN_BH_WLOCK();
	fs = dn_ht_find(dn_cfg.fshash, i, DNHT_REMOVE, NULL);
	ND("fs %d found %p", i, fs);
	if (fs) {
		fsk_detach(fs, DN_DETACH | DN_DELETE_FS);
		err = 0;
	} else
		err = EINVAL;
	if (!locked)
		DN_BH_WUNLOCK();
	return err;
}