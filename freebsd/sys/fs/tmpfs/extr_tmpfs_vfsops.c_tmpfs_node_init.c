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
struct tmpfs_node {int /*<<< orphan*/  tn_gen; int /*<<< orphan*/  tn_interlock; scalar_t__ tn_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmpfs_node_init(void *mem, int size, int flags)
{
	struct tmpfs_node *node = (struct tmpfs_node *)mem;
	node->tn_id = 0;

	mtx_init(&node->tn_interlock, "tmpfs node interlock", NULL, MTX_DEF);
	node->tn_gen = arc4random();

	return (0);
}