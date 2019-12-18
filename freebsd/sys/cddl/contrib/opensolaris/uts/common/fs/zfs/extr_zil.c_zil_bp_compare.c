#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  zn_dva; } ;
typedef  TYPE_1__ zil_bp_node_t ;
typedef  int /*<<< orphan*/  dva_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
zil_bp_compare(const void *x1, const void *x2)
{
	const dva_t *dva1 = &((zil_bp_node_t *)x1)->zn_dva;
	const dva_t *dva2 = &((zil_bp_node_t *)x2)->zn_dva;

	int cmp = AVL_CMP(DVA_GET_VDEV(dva1), DVA_GET_VDEV(dva2));
	if (likely(cmp))
		return (cmp);

	return (AVL_CMP(DVA_GET_OFFSET(dva1), DVA_GET_OFFSET(dva2)));
}