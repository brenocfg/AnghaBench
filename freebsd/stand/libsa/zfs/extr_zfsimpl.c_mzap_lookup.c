#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_2__* mz_chunk; } ;
typedef  TYPE_1__ mzap_phys_t ;
struct TYPE_6__ {int /*<<< orphan*/  mze_value; int /*<<< orphan*/  mze_name; } ;
typedef  TYPE_2__ mzap_ent_phys_t ;
struct TYPE_7__ {int dn_datablkszsec; } ;
typedef  TYPE_3__ dnode_phys_t ;

/* Variables and functions */
 int ENOENT ; 
 size_t MZAP_ENT_LEN ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ zap_scratch ; 

__attribute__((used)) static int
mzap_lookup(const dnode_phys_t *dnode, const char *name, uint64_t *value)
{
	const mzap_phys_t *mz;
	const mzap_ent_phys_t *mze;
	size_t size;
	int chunks, i;

	/*
	 * Microzap objects use exactly one block. Read the whole
	 * thing.
	 */
	size = dnode->dn_datablkszsec * 512;

	mz = (const mzap_phys_t *) zap_scratch;
	chunks = size / MZAP_ENT_LEN - 1;

	for (i = 0; i < chunks; i++) {
		mze = &mz->mz_chunk[i];
		if (!strcmp(mze->mze_name, name)) {
			*value = mze->mze_value;
			return (0);
		}
	}

	return (ENOENT);
}