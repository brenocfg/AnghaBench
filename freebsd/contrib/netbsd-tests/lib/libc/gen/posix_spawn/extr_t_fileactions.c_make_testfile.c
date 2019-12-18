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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  TESTCONTENT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fwrite (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_testfile(const char *restrict file)
{
	FILE *f;
	size_t written;

	f = fopen(file, "w");
	ATF_REQUIRE(f != NULL);
	written = fwrite(TESTCONTENT, 1, strlen(TESTCONTENT), f);
	fclose(f);
	ATF_REQUIRE(written == strlen(TESTCONTENT));
}