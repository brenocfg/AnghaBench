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
typedef  int u_int64_t ;
struct node_queue_bw {scalar_t__ bw_absolute; int bw_percent; } ;

/* Variables and functions */
 int MIN (scalar_t__,int) ; 

u_int64_t
eval_bwspec(struct node_queue_bw *bw, u_int64_t ref_bw)
{
	if (bw->bw_absolute > 0)
		return (MIN(bw->bw_absolute, ref_bw));

	if (bw->bw_percent > 0)
		return (ref_bw / 100 * bw->bw_percent);

	return (0);
}