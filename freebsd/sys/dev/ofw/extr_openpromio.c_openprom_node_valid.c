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
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int openprom_node_search (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
openprom_node_valid(phandle_t node)
{

	if (node == 0)
		return (0);
	return (openprom_node_search(OF_peer(0), node));
}