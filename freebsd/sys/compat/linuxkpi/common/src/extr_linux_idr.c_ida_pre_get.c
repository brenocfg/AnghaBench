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
struct ida_bitmap {int dummy; } ;
struct ida {int /*<<< orphan*/ * free_bitmap; int /*<<< orphan*/  idr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_IDR ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ida_pre_get(struct ida *ida, gfp_t flags)
{
	if (idr_pre_get(&ida->idr, flags) == 0)
		return (0);

	if (ida->free_bitmap == NULL) {
		ida->free_bitmap =
		    malloc(sizeof(struct ida_bitmap), M_IDR, flags);
	}
	return (ida->free_bitmap != NULL);
}