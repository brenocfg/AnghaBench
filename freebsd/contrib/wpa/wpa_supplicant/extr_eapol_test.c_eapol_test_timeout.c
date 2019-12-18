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
struct eapol_test_data {int auth_timed_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void eapol_test_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct eapol_test_data *e = eloop_ctx;
	printf("EAPOL test timed out\n");
	e->auth_timed_out = 1;
	eloop_terminate();
}