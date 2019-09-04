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
 scalar_t__ ctx ; 
 scalar_t__ ctx_peer ; 
 int /*<<< orphan*/  test_resumption_impl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_resumption_different_preferred_key_share(void)
{
    if (ctx == ctx_peer)
        return;
    test_resumption_impl(1, 0);
}