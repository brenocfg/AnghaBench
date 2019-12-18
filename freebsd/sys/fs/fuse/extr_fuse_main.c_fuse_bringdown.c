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
typedef  int /*<<< orphan*/  eventhandler_tag ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_device_destroy () ; 
 int /*<<< orphan*/  fuse_file_destroy () ; 
 int /*<<< orphan*/  fuse_internal_destroy () ; 
 int /*<<< orphan*/  fuse_ipc_destroy () ; 
 int /*<<< orphan*/  fuse_mtx ; 
 int /*<<< orphan*/  fuse_node_destroy () ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fuse_bringdown(eventhandler_tag eh_tag)
{
	fuse_node_destroy();
	fuse_internal_destroy();
	fuse_file_destroy();
	fuse_ipc_destroy();
	fuse_device_destroy();
	mtx_destroy(&fuse_mtx);
}