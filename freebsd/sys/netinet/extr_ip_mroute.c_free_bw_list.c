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
struct bw_meter {struct bw_meter* bm_mfc_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BWMETER ; 
 int /*<<< orphan*/  free (struct bw_meter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unschedule_bw_meter (struct bw_meter*) ; 

__attribute__((used)) static void
free_bw_list(struct bw_meter *list)
{
    while (list != NULL) {
	struct bw_meter *x = list;

	list = list->bm_mfc_next;
	unschedule_bw_meter(x);
	free(x, M_BWMETER);
    }
}