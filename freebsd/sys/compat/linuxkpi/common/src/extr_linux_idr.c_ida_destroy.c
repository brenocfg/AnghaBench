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
struct ida {int /*<<< orphan*/  free_bitmap; int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IDR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 

void
ida_destroy(struct ida *ida)
{
	idr_destroy(&ida->idr);
	free(ida->free_bitmap, M_IDR);
}