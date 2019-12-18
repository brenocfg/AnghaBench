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
struct atmif_reg {TYPE_1__* aif; } ;
struct TYPE_2__ {int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct atmif_reg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct atmif_reg*) ; 
 int /*<<< orphan*/  link ; 

void
atm_unnotify_aif(void *arg)
{
	struct atmif_reg *r0 = arg;

	TAILQ_REMOVE(&r0->aif->notify, r0, link);
	free(r0);
}