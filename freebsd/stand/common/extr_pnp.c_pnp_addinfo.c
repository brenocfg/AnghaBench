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
struct pnpinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pnpinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_link ; 
 int /*<<< orphan*/  pnp_devices ; 

void
pnp_addinfo(struct pnpinfo *pi)
{
    STAILQ_INSERT_TAIL(&pnp_devices, pi, pi_link);
}