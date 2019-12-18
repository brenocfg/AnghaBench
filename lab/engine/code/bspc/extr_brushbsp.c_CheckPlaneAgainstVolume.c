#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  volume; } ;
typedef  TYPE_1__ node_t ;
typedef  int /*<<< orphan*/  bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SplitBrush (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

qboolean CheckPlaneAgainstVolume (int pnum, node_t *node)
{
	bspbrush_t	*front, *back;
	qboolean	good;

	SplitBrush (node->volume, pnum, &front, &back);

	good = (front && back);

	if (front) FreeBrush (front);
	if (back) FreeBrush (back);

	return good;
}