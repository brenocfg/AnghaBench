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
 struct pnpinfo* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_link ; 
 int /*<<< orphan*/  pnp_devices ; 
 int /*<<< orphan*/  pnp_freeinfo (struct pnpinfo*) ; 

__attribute__((used)) static void
pnp_discard(void)
{
    struct pnpinfo	*pi;

    while (STAILQ_FIRST(&pnp_devices) != NULL) {
	pi = STAILQ_FIRST(&pnp_devices);
	STAILQ_REMOVE_HEAD(&pnp_devices, pi_link);
	pnp_freeinfo(pi);
    }
}