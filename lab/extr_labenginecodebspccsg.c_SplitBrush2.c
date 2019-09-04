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
typedef  int /*<<< orphan*/  bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  SplitBrush (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

void SplitBrush2 (bspbrush_t *brush, int planenum,
	bspbrush_t **front, bspbrush_t **back)
{
	SplitBrush (brush, planenum, front, back);
#if 0
	if (*front && (*front)->sides[(*front)->numsides-1].texinfo == -1)
		(*front)->sides[(*front)->numsides-1].texinfo = (*front)->sides[0].texinfo;	// not -1
	if (*back && (*back)->sides[(*back)->numsides-1].texinfo == -1)
		(*back)->sides[(*back)->numsides-1].texinfo = (*back)->sides[0].texinfo;	// not -1
#endif
}