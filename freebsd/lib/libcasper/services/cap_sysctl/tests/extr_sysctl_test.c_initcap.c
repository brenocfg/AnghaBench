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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL0_FILE ; 
 int /*<<< orphan*/  SYSCTL0_NAME ; 
 int /*<<< orphan*/  SYSCTL1_FILE ; 
 int /*<<< orphan*/  SYSCTL1_NAME ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  save_int_sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cap_channel_t *
initcap(void)
{
	cap_channel_t *capcas, *capsysctl;

	save_int_sysctl(SYSCTL0_NAME, SYSCTL0_FILE);
	save_int_sysctl(SYSCTL1_NAME, SYSCTL1_FILE);

	capcas = cap_init();
	ATF_REQUIRE(capcas != NULL);

	capsysctl = cap_service_open(capcas, "system.sysctl");
	ATF_REQUIRE(capsysctl != NULL);

	cap_close(capcas);

	return (capsysctl);
}