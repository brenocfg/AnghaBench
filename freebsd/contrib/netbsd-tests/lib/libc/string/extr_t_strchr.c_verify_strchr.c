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
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,int,unsigned int,unsigned int) ; 
 char* slow_strchr (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr_fn (char*,int) ; 

__attribute__((used)) static void
verify_strchr(char *buf, int ch, unsigned int t, unsigned int a)
{
	const char *off, *ok_off;

	off = strchr_fn(buf, ch);
	ok_off = slow_strchr(buf, ch);
	if (off == ok_off)
		return;

	fprintf(stderr, "test_strchr(\"%s\", %#x) gave %zd not %zd (test %d, "
	    "alignment %d)\n",
	    buf, ch, off ? off - buf : -1, ok_off ? ok_off - buf : -1, t, a);

	atf_tc_fail("Check stderr for details");
}