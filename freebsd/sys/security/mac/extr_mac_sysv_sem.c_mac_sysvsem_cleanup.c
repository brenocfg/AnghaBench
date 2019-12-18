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
struct semid_kernel {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysvsem_cleanup ; 

void
mac_sysvsem_cleanup(struct semid_kernel *semakptr)
{

	MAC_POLICY_PERFORM_NOSLEEP(sysvsem_cleanup, semakptr->label);
}