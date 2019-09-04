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
 int /*<<< orphan*/  test_load_tickets_file ; 
 int /*<<< orphan*/  test_memcached_ticket_update ; 
 int /*<<< orphan*/  test_serialize_tickets ; 

void test_src__ssl_c(void)
{
    subtest("load-tickets-file", test_load_tickets_file);
    subtest("serialize-tickets", test_serialize_tickets);
    subtest("memcached-ticket-update", test_memcached_ticket_update);
}