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
 int COLL_WEIGHTS_MAX ; 
 int T_CHAR ; 
 scalar_t__ T_ELLIPSIS ; 
 scalar_t__ curr_weight ; 
 scalar_t__ currorder ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lastorder ; 
 int* order_weights ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
start_order(int type)
{
	int	i;

	lastorder = currorder;
	currorder = type;

	/* this is used to protect ELLIPSIS processing */
	if ((lastorder == T_ELLIPSIS) && (type != T_CHAR)) {
		fprintf(stderr, "character value expected");
	}

	for (i = 0; i < COLL_WEIGHTS_MAX; i++) {
		order_weights[i] = -1;
	}
	curr_weight = 0;
}