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
 int /*<<< orphan*/  test_at_position ; 
 int /*<<< orphan*/  test_decode_base64 ; 
 int /*<<< orphan*/  test_get_filext ; 
 int /*<<< orphan*/  test_htmlescape ; 
 int /*<<< orphan*/  test_next_token ; 
 int /*<<< orphan*/  test_next_token2 ; 
 int /*<<< orphan*/  test_next_token3 ; 
 int /*<<< orphan*/  test_stripws ; 
 int /*<<< orphan*/  test_strstr ; 
 int /*<<< orphan*/  test_uri_escape ; 

void test_lib__common__string_c(void)
{
    subtest("strstr", test_strstr);
    subtest("stripws", test_stripws);
    subtest("get_filext", test_get_filext);
    subtest("next_token", test_next_token);
    subtest("next_token2", test_next_token2);
    subtest("next_token3", test_next_token3);
    subtest("decode_base64", test_decode_base64);
    subtest("htmlescape", test_htmlescape);
    subtest("uri_escape", test_uri_escape);
    subtest("at_position", test_at_position);
}