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
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_call_void_op (struct fwnode_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put ; 

void fwnode_handle_put(struct fwnode_handle *fwnode)
{
	fwnode_call_void_op(fwnode, put);
}