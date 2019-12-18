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
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  ng_item_fn ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_NOFLAGS ; 
 int ng_send_fn1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 

int
ng_send_fn(node_p node, hook_p hook, ng_item_fn *fn, void * arg1, int arg2)
{

	return ng_send_fn1(node, hook, fn, arg1, arg2, NG_NOFLAGS);
}