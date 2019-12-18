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
struct statsblob_tpl {TYPE_2__* mb; TYPE_3__* sb; } ;
struct TYPE_7__ {int /*<<< orphan*/  cursz; } ;
struct TYPE_6__ {void* tplhash; TYPE_1__* voi_meta; int /*<<< orphan*/ * tplname; } ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int NVOIS (TYPE_3__*) ; 
 int /*<<< orphan*/  TPL_LIST_WLOCK_ASSERT () ; 
 void* hash32_buf (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 void* hash32_str (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void
stats_tpl_update_hash(struct statsblob_tpl *tpl)
{

	TPL_LIST_WLOCK_ASSERT();
	tpl->mb->tplhash = hash32_str(tpl->mb->tplname, 0);
	for (int voi_id = 0; voi_id < NVOIS(tpl->sb); voi_id++) {
		if (tpl->mb->voi_meta[voi_id].name != NULL)
			tpl->mb->tplhash = hash32_str(
			    tpl->mb->voi_meta[voi_id].name, tpl->mb->tplhash);
	}
	tpl->mb->tplhash = hash32_buf(tpl->sb, tpl->sb->cursz,
	    tpl->mb->tplhash);
}