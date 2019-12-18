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
 int /*<<< orphan*/  expect_decode_pass (char*,char*) ; 

void test_buf_percent__ignores_invalid(void)
{
	expect_decode_pass("githu%%.com", "githu%%.com");
	expect_decode_pass("github.co%2", "github.co%2");
	expect_decode_pass("github%2.com", "github%2.com");
	expect_decode_pass("githu%2z.com", "githu%2z.com");
	expect_decode_pass("github.co%9z", "github.co%9z");
	expect_decode_pass("github.co%2", "github.co%2");
	expect_decode_pass("github.co%", "github.co%");
}