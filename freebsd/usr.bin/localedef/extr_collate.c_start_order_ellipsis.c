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
 int NUM_WT ; 
 scalar_t__ T_CHAR ; 
 int /*<<< orphan*/  T_ELLIPSIS ; 
 int /*<<< orphan*/ * ellipsis_weights ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lastorder ; 
 int /*<<< orphan*/ * order_weights ; 
 int /*<<< orphan*/  start_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
start_order_ellipsis(void)
{
	int	i;

	start_order(T_ELLIPSIS);

	if (lastorder != T_CHAR) {
		fprintf(stderr, "illegal starting point for range");
		return;
	}

	for (i = 0; i < NUM_WT; i++) {
		ellipsis_weights[i] = order_weights[i];
	}
}