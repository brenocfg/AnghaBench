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
struct g_llvm_vg {int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  vg_lvs; int /*<<< orphan*/  vg_pvs; } ;
struct g_llvm_segment {int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  vg_lvs; int /*<<< orphan*/  vg_pvs; } ;
struct g_llvm_pv {int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  vg_lvs; int /*<<< orphan*/  vg_pvs; } ;
struct g_llvm_lv {int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  vg_lvs; int /*<<< orphan*/  vg_pvs; } ;

/* Variables and functions */
 struct g_llvm_vg* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_llvm_vg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GLLVM ; 
 int /*<<< orphan*/  free (struct g_llvm_vg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv_next ; 
 int /*<<< orphan*/  pv_next ; 
 int /*<<< orphan*/  sg_next ; 
 int /*<<< orphan*/  vg_next ; 

__attribute__((used)) static void
g_llvm_free_vg(struct g_llvm_vg *vg)
{
	struct g_llvm_pv *pv;
	struct g_llvm_lv *lv;
	struct g_llvm_segment *sg;

	/* Free all the structures */
	while ((pv = LIST_FIRST(&vg->vg_pvs)) != NULL) {
		LIST_REMOVE(pv, pv_next);
		free(pv, M_GLLVM);
	}
	while ((lv = LIST_FIRST(&vg->vg_lvs)) != NULL) {
		while ((sg = LIST_FIRST(&lv->lv_segs)) != NULL) {
			LIST_REMOVE(sg, sg_next);
			free(sg, M_GLLVM);
		}
		LIST_REMOVE(lv, lv_next);
		free(lv, M_GLLVM);
	}
	LIST_REMOVE(vg, vg_next);
	free(vg, M_GLLVM);
}