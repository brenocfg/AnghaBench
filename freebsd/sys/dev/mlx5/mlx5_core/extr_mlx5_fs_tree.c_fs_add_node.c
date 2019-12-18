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
struct fs_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _fs_add_node (struct fs_base*,char const*,struct fs_base*) ; 
 int /*<<< orphan*/  fs_init_node (struct fs_base*,unsigned int) ; 

__attribute__((used)) static void fs_add_node(struct fs_base *node,
			struct fs_base *parent, const char *name,
			unsigned int refcount)
{
	fs_init_node(node, refcount);
	_fs_add_node(node, name, parent);
}