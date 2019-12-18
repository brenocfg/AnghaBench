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
 int /*<<< orphan*/  assert_matches (char*,char*,int,int,int,int) ; 

void test_core_wildmatch__character_classes(void)
{
	assert_matches("a1B", "[[:alpha:]][[:digit:]][[:upper:]]", 1, 1, 1, 1);
	assert_matches("a", "[[:digit:][:upper:][:space:]]", 0, 1, 0, 1);
	assert_matches("A", "[[:digit:][:upper:][:space:]]", 1, 1, 1, 1);
	assert_matches("1", "[[:digit:][:upper:][:space:]]", 1, 1, 1, 1);
	assert_matches("1", "[[:digit:][:upper:][:spaci:]]", 0, 0, 0, 0);
	assert_matches(" ", "[[:digit:][:upper:][:space:]]", 1, 1, 1, 1);
	assert_matches(".", "[[:digit:][:upper:][:space:]]", 0, 0, 0, 0);
	assert_matches(".", "[[:digit:][:punct:][:space:]]", 1, 1, 1, 1);
	assert_matches("5", "[[:xdigit:]]", 1, 1, 1, 1);
	assert_matches("f", "[[:xdigit:]]", 1, 1, 1, 1);
	assert_matches("D", "[[:xdigit:]]", 1, 1, 1, 1);
	assert_matches("_", "[[:alnum:][:alpha:][:blank:][:cntrl:][:digit:][:graph:][:lower:][:print:][:punct:][:space:][:upper:][:xdigit:]]", 1, 1, 1, 1);
	assert_matches(".", "[^[:alnum:][:alpha:][:blank:][:cntrl:][:digit:][:lower:][:space:][:upper:][:xdigit:]]", 1, 1, 1, 1);
	assert_matches("5", "[a-c[:digit:]x-z]", 1, 1, 1, 1);
	assert_matches("b", "[a-c[:digit:]x-z]", 1, 1, 1, 1);
	assert_matches("y", "[a-c[:digit:]x-z]", 1, 1, 1, 1);
	assert_matches("q", "[a-c[:digit:]x-z]", 0, 0, 0, 0);
}