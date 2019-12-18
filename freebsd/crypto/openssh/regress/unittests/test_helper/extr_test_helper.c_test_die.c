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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  onerror_ctx ; 
 int /*<<< orphan*/  test_onerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_die(void)
{
	if (test_onerror != NULL)
		test_onerror(onerror_ctx);
	abort();
}