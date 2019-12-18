#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wint_t ;
struct cmap {scalar_t__ cm_def; TYPE_1__* cm_root; } ;
struct TYPE_3__ {scalar_t__ cmn_from; scalar_t__ cmn_to; } ;

/* Variables and functions */
 scalar_t__ CM_DEF_SELF ; 
 TYPE_1__* cmap_splay (TYPE_1__*,scalar_t__) ; 

wint_t
cmap_lookup_hard(struct cmap *cm, wint_t ch)
{

	if (cm->cm_root != NULL) {
		cm->cm_root = cmap_splay(cm->cm_root, ch);
		if (cm->cm_root->cmn_from == ch)
			return (cm->cm_root->cmn_to);
	}
	return (cm->cm_def == CM_DEF_SELF ? ch : cm->cm_def);
}