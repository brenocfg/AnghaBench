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

/* Variables and functions */
 int /*<<< orphan*/  free_exp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * v4root_ep ; 

__attribute__((used)) static void
free_v4rootexp(void)
{

	if (v4root_ep != NULL) {
		free_exp(v4root_ep);
		v4root_ep = NULL;
	}
}