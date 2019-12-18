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
typedef  int /*<<< orphan*/  busdma_seg_t ;
typedef  int /*<<< orphan*/  busdma_md_t ;

/* Variables and functions */
 int /*<<< orphan*/  bd_md_first_seg (int /*<<< orphan*/ ,int) ; 

busdma_seg_t
busdma_md_first_seg(busdma_md_t md, int space)
{
	busdma_seg_t seg;

	seg = bd_md_first_seg(md, space);
	return (seg);
}