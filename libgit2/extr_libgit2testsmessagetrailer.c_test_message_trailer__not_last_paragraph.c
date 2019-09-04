#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ git_message_trailer ;

/* Variables and functions */
 int /*<<< orphan*/  assert_trailers (char*,TYPE_1__*) ; 

void test_message_trailer__not_last_paragraph(void)
{
	git_message_trailer trailers[] = {
		{NULL, NULL},
	};

	assert_trailers(
		"Message\n"
		"\n"
		"Key: value\n"
		"\n"
		"More stuff\n"
	, trailers);
}