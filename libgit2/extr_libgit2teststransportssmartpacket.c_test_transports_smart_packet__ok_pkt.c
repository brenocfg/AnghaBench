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
 int /*<<< orphan*/  assert_ok_parses (char*,char*) ; 
 int /*<<< orphan*/  assert_pkt_fails (char*) ; 

void test_transports_smart_packet__ok_pkt(void)
{
	assert_pkt_fails("0007ok\n");
	assert_ok_parses("0007ok ", "");
	assert_ok_parses("0008ok \n", "");
	assert_ok_parses("0008ok x", "x");
	assert_ok_parses("0009ok x\n", "x");
	assert_pkt_fails("001OK ref/foo/bar");
	assert_ok_parses("0012ok ref/foo/bar", "ref/foo/bar");
	assert_pkt_fails("0013OK ref/foo/bar\n");
	assert_ok_parses("0013ok ref/foo/bar\n", "ref/foo/bar");
}