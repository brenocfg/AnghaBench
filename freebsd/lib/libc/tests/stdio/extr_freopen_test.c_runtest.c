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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*,char const*,char const*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/ * freopen (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
runtest(const char *fname1, const char *mode1, const char *fname2,
    const char *mode2, bool success)
{
	FILE *fp1, *fp2;
	const char *fname2_print;

	fname2_print = fname2 != NULL ? fname2 : "<NULL>";
	fp1 = fopen(fname1, mode1);
	ATF_REQUIRE_MSG(fp1 != NULL,
	    "fopen(\"%s\", \"%s\") failed; errno=%d", fname1, mode1, errno);
	fp2 = freopen(fname2, mode2, fp1);
	if (fp2 == NULL) {
		ATF_REQUIRE_MSG(success == false,
		    "freopen(\"%s\", \"%s\", fopen(\"%s\", \"%s\")) succeeded "
		    "unexpectedly", fname2_print, mode2, fname1, mode1);
		return;
	}
	ATF_REQUIRE_MSG(success == true,
	    "freopen(\"%s\", \"%s\", fopen(\"%s\", \"%s\")) failed: %d",
	    fname2_print, mode2, fname1, mode1, errno);
	fclose(fp2);
}