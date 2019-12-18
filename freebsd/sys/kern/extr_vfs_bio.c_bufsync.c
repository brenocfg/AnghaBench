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
struct bufobj {int dummy; } ;

/* Variables and functions */
 int VOP_FSYNC (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo2vnode (struct bufobj*) ; 
 int /*<<< orphan*/  curthread ; 

int
bufsync(struct bufobj *bo, int waitfor)
{

	return (VOP_FSYNC(bo2vnode(bo), waitfor, curthread));
}