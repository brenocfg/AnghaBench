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
typedef  int /*<<< orphan*/  buff2 ;
typedef  int /*<<< orphan*/  buff1 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logprintf (char*,char const*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

int
assertion_equal_file(const char *filename, int line, const char *fn1, const char *fn2)
{
	char buff1[1024];
	char buff2[1024];
	FILE *f1, *f2;
	int n1, n2;

	assertion_count(filename, line);

	f1 = fopen(fn1, "rb");
	f2 = fopen(fn2, "rb");
	if (f1 == NULL || f2 == NULL) {
		if (f1) fclose(f1);
		if (f2) fclose(f2);
		return (0);
	}
	for (;;) {
		n1 = (int)fread(buff1, 1, sizeof(buff1), f1);
		n2 = (int)fread(buff2, 1, sizeof(buff2), f2);
		if (n1 != n2)
			break;
		if (n1 == 0 && n2 == 0) {
			fclose(f1);
			fclose(f2);
			return (1);
		}
		if (memcmp(buff1, buff2, n1) != 0)
			break;
	}
	fclose(f1);
	fclose(f2);
	failure_start(filename, line, "Files not identical");
	logprintf("  file1=\"%s\"\n", fn1);
	logprintf("  file2=\"%s\"\n", fn2);
	failure_finish(NULL);
	return (0);
}