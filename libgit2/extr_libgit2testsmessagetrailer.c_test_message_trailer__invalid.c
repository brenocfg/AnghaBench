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
struct TYPE_3__ {char* member_0; char* member_1; } ;
typedef  TYPE_1__ git_message_trailer ;

/* Variables and functions */
 int /*<<< orphan*/  assert_trailers (char*,TYPE_1__*) ; 

void test_message_trailer__invalid(void)
{
	git_message_trailer trailers[] = {
		{"Signed-off-by", "some@one.com"},
		{"Another", "trailer"},
		{NULL, NULL},
	};

	assert_trailers(
		"Message\n"
		"\n"
		"Signed-off-by: some@one.com\n"
		"Not a trailer\n"
		"Another: trailer\n"
	, trailers);
}