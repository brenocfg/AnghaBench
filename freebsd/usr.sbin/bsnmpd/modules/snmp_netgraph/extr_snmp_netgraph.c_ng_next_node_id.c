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
typedef  int /*<<< orphan*/  ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  ng_next_node_id_internal (int /*<<< orphan*/ ,char const*,char const*,int) ; 

ng_ID_t
ng_next_node_id(ng_ID_t node, const char *type, const char *hook)
{
	return (ng_next_node_id_internal(node, type, hook, 1));
}