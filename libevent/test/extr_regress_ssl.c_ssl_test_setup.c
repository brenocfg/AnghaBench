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
struct testcase_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 void* basic_test_setup (struct testcase_t const*) ; 
 scalar_t__ disable_tls_11_and_12 ; 
 int /*<<< orphan*/  init_ssl () ; 
 int /*<<< orphan*/  ssl_getcert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_getkey () ; 
 int /*<<< orphan*/  the_cert ; 
 int /*<<< orphan*/  the_key ; 

__attribute__((used)) static void *
ssl_test_setup(const struct testcase_t *testcase)
{
	init_ssl();

	the_key = ssl_getkey();
	EVUTIL_ASSERT(the_key);

	the_cert = ssl_getcert(the_key);
	EVUTIL_ASSERT(the_cert);

	disable_tls_11_and_12 = 0;

	return basic_test_setup(testcase);
}