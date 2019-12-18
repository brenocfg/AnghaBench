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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_recv (int,int) ; 
 scalar_t__ nvlist_send (int,int /*<<< orphan*/ *) ; 

nvlist_t *
nvlist_xfer(int sock, nvlist_t *nvl, int flags)
{

	if (nvlist_send(sock, nvl) < 0) {
		nvlist_destroy(nvl);
		return (NULL);
	}
	nvlist_destroy(nvl);
	return (nvlist_recv(sock, flags));
}