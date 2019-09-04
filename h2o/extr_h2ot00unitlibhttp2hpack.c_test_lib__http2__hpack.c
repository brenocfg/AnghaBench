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
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_hpack ; 
 int /*<<< orphan*/  test_hpack_dynamic_table ; 
 int /*<<< orphan*/  test_hpack_push ; 
 int /*<<< orphan*/  test_token_wo_hpack_id ; 

void test_lib__http2__hpack(void)
{
    subtest("hpack", test_hpack);
    subtest("hpack-push", test_hpack_push);
    subtest("hpack-dynamic-table", test_hpack_dynamic_table);
    subtest("token-wo-hpack-id", test_token_wo_hpack_id);
}