#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* head; } ;
typedef  TYPE_1__ chastore_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ chanode_t ;

/* Variables and functions */
 int /*<<< orphan*/  xdl_free (TYPE_2__*) ; 

void xdl_cha_free(chastore_t *cha) {
	chanode_t *cur, *tmp;

	for (cur = cha->head; (tmp = cur) != NULL;) {
		cur = cur->next;
		xdl_free(tmp);
	}
}