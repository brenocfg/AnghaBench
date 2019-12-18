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
struct celockstate {int /*<<< orphan*/ ** vlp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cache_unlock_vnodes_cel(struct celockstate *cel)
{

	MPASS(cel->vlp[0] != NULL || cel->vlp[1] != NULL);

	if (cel->vlp[0] != NULL)
		mtx_unlock(cel->vlp[0]);
	if (cel->vlp[1] != NULL)
		mtx_unlock(cel->vlp[1]);
	if (cel->vlp[2] != NULL)
		mtx_unlock(cel->vlp[2]);
}