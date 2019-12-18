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
 int /*<<< orphan*/  assert_comment_parses (char*,char*) ; 

void test_transports_smart_packet__comment_pkt(void)
{
	assert_comment_parses("0005#", "");
	assert_comment_parses("000B#foobar", "#fooba");
	assert_comment_parses("000C#foobar", "#foobar");
	assert_comment_parses("001A#this is a comment\nfoo", "#this is a comment\nfoo");
}