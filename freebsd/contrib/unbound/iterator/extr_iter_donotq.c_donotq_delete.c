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
struct iter_donotq {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct iter_donotq*) ; 
 int /*<<< orphan*/  regional_destroy (int /*<<< orphan*/ ) ; 

void 
donotq_delete(struct iter_donotq* dq)
{
	if(!dq) 
		return;
	regional_destroy(dq->region);
	free(dq);
}