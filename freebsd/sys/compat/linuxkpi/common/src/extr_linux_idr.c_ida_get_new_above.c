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
struct ida {int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int idr_get_new_above (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

int
ida_get_new_above(struct ida *ida, int starting_id, int *p_id)
{
	return (idr_get_new_above(&ida->idr, NULL, starting_id, p_id));
}