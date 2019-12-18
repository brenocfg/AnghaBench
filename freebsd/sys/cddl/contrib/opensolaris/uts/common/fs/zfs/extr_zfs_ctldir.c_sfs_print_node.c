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
typedef  char* uintmax_t ;
struct TYPE_3__ {char* sn_name; scalar_t__ sn_id; scalar_t__ sn_parent_id; } ;
typedef  TYPE_1__ sfs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
sfs_print_node(sfs_node_t *node)
{
	printf("\tname = %s\n", node->sn_name);
	printf("\tparent_id = %ju\n", (uintmax_t)node->sn_parent_id);
	printf("\tid = %ju\n", (uintmax_t)node->sn_id);
}