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
struct pipepair {int /*<<< orphan*/ * pp_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_pipe_label_free (int /*<<< orphan*/ *) ; 

void
mac_pipe_destroy(struct pipepair *pp)
{

	if (pp->pp_label != NULL) {
		mac_pipe_label_free(pp->pp_label);
		pp->pp_label = NULL;
	}
}