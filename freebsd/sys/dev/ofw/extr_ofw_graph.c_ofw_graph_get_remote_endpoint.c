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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

phandle_t
ofw_graph_get_remote_endpoint(phandle_t endpoint)
{
	phandle_t remote;

	if (OF_getencprop(endpoint, "remote-endpoint", &remote,
	      sizeof(phandle_t)) <= 0)
		return (0);

	return (remote);
}