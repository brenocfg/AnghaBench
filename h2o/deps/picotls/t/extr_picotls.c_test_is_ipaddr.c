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
 int /*<<< orphan*/  ok (int) ; 
 int ptls_server_name_is_ipaddr (char*) ; 

__attribute__((used)) static void test_is_ipaddr(void)
{
    ok(!ptls_server_name_is_ipaddr("www.google.com"));
    ok(!ptls_server_name_is_ipaddr("www.google.com."));
    ok(!ptls_server_name_is_ipaddr("www"));
    ok(!ptls_server_name_is_ipaddr(""));
    ok(!ptls_server_name_is_ipaddr("123"));
    ok(ptls_server_name_is_ipaddr("1.1.1.1"));
    ok(ptls_server_name_is_ipaddr("2001:db8::2:1"));
}