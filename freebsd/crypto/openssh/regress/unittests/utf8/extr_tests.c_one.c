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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int,int) ; 
 int /*<<< orphan*/  ASSERT_STRING_EQ (char*,char const*) ; 
 int /*<<< orphan*/  TEST_DONE () ; 
 int /*<<< orphan*/  TEST_START (char*) ; 
 int snmprintf (char*,int,int*,char*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
one(int utf8, const char *name, const char *mbs, int width,
    int wantwidth, int wantlen, const char *wants)
{
	char	 buf[16];
	int	*wp;
	int	 len;

	if (wantlen == -2)
		wantlen = strlen(wants);
	(void)strlcpy(buf, utf8 ? "utf8_" : "c_", sizeof(buf));
	(void)strlcat(buf, name, sizeof(buf));
	TEST_START(buf);
	wp = wantwidth == -2 ? NULL : &width;
	len = snmprintf(buf, sizeof(buf), wp, "%s", mbs);
	ASSERT_INT_EQ(len, wantlen);
	ASSERT_STRING_EQ(buf, wants);
	ASSERT_INT_EQ(width, wantwidth);
	TEST_DONE();
}