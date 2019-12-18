#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * su_tail_data; int /*<<< orphan*/ * rr_relocated; int /*<<< orphan*/  rr_real_parent; int /*<<< orphan*/ * isoExtAttributes; int /*<<< orphan*/ * isoDirRecord; int /*<<< orphan*/ * node; int /*<<< orphan*/ * ptlast; int /*<<< orphan*/  ptprev; int /*<<< orphan*/  ptnext; int /*<<< orphan*/ * dot_dot_record; int /*<<< orphan*/  dot_record; int /*<<< orphan*/  parent; int /*<<< orphan*/  cn_children; } ;
typedef  TYPE_1__ cd9660node ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecalloc (int,int) ; 

__attribute__((used)) static cd9660node *
cd9660_allocate_cd9660node(void)
{
	cd9660node *temp = ecalloc(1, sizeof(*temp));

	TAILQ_INIT(&temp->cn_children);
	temp->parent = temp->dot_record = temp->dot_dot_record = NULL;
	temp->ptnext = temp->ptprev = temp->ptlast = NULL;
	temp->node = NULL;
	temp->isoDirRecord = NULL;
	temp->isoExtAttributes = NULL;
	temp->rr_real_parent = temp->rr_relocated = NULL;
	temp->su_tail_data = NULL;
	return temp;
}