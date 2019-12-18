#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_tag_fails (char const*,scalar_t__) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_error_last () ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 

void test_object_tag_parse__no_oob_read_when_searching_message(void)
{
	const char *tag =
		"object a8d447f68076d1520f69649bb52629941be7031f\n"
		"type tag\n"
		"tag \n"
		"tagger <>\n"
		" \n\n"
		"Message";
	/*
	 * The OOB read previously resulted in an OOM error. We
	 * thus want to make sure that the resulting error is the
	 * expected one.
	 */
	assert_tag_fails(tag, strlen(tag) - strlen("\n\nMessage"));
	cl_assert(strstr(git_error_last()->message, "tag contains no message"));
}