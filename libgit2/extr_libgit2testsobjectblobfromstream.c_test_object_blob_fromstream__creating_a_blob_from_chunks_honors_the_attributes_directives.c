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
 int /*<<< orphan*/  assert_named_chunked_blob (char*,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  write_attributes (int /*<<< orphan*/ ) ; 

void test_object_blob_fromstream__creating_a_blob_from_chunks_honors_the_attributes_directives(void)
{
	write_attributes(repo);

	assert_named_chunked_blob("321cbdf08803c744082332332838df6bd160f8f9", "dummy.data");
	assert_named_chunked_blob("e9671e138a780833cb689753570fd10a55be84fb", "dummy.txt");
	assert_named_chunked_blob("e9671e138a780833cb689753570fd10a55be84fb", "dummy.dunno");
}