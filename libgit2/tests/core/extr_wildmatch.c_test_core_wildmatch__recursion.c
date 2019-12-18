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

void test_core_wildmatch__recursion(void)
{
	assert_matches("-adobe-courier-bold-o-normal--12-120-75-75-m-70-iso8859-1", "-*-*-*-*-*-*-12-*-*-*-m-*-*-*", 1, 1, 1, 1);
	assert_matches("-adobe-courier-bold-o-normal--12-120-75-75-X-70-iso8859-1", "-*-*-*-*-*-*-12-*-*-*-m-*-*-*", 0, 0, 0, 0);
	assert_matches("-adobe-courier-bold-o-normal--12-120-75-75-/-70-iso8859-1", "-*-*-*-*-*-*-12-*-*-*-m-*-*-*", 0, 0, 0, 0);
	assert_matches("XXX/adobe/courier/bold/o/normal//12/120/75/75/m/70/iso8859/1", "XXX/*/*/*/*/*/*/12/*/*/*/m/*/*/*", 1, 1, 1, 1);
	assert_matches("XXX/adobe/courier/bold/o/normal//12/120/75/75/X/70/iso8859/1", "XXX/*/*/*/*/*/*/12/*/*/*/m/*/*/*", 0, 0, 0, 0);
	assert_matches("abcd/abcdefg/abcdefghijk/abcdefghijklmnop.txt", "**/*a*b*g*n*t", 1, 1, 1, 1);
	assert_matches("abcd/abcdefg/abcdefghijk/abcdefghijklmnop.txtz", "**/*a*b*g*n*t", 0, 0, 0, 0);
	assert_matches("foo", "*/*/*", 0, 0, 0, 0);
	assert_matches("foo/bar", "*/*/*", 0, 0, 0, 0);
	assert_matches("foo/bba/arr", "*/*/*", 1, 1, 1, 1);
	assert_matches("foo/bb/aa/rr", "*/*/*", 0, 0, 1, 1);
	assert_matches("foo/bb/aa/rr", "**/**/**", 1, 1, 1, 1);
	assert_matches("abcXdefXghi", "*X*i", 1, 1, 1, 1);
	assert_matches("ab/cXd/efXg/hi", "*X*i", 0, 0, 1, 1);
	assert_matches("ab/cXd/efXg/hi", "*/*X*/*/*i", 1, 1, 1, 1);
	assert_matches("ab/cXd/efXg/hi", "**/*X*/**/*i", 1, 1, 1, 1);
}