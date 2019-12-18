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
struct ifnet {void* if_start; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */

void
if_setstartfn(if_t ifp, void (*start_fn)(if_t))
{
	((struct ifnet *)ifp)->if_start = (void *)start_fn;
}