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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_attach_internal (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
if_attach(struct ifnet *ifp)
{

	if_attach_internal(ifp, 0, NULL);
}