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
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

int
main()
{
	int i = 1;
	char buf[256];
	char *msg = "rename() fails to handle race situation\n";

	switch (fork()) {
	case -1:
		perror("fork");
		exit(1);
		break;
	case 0:
		while (i > 0) {
			int c_count = 0;
			if (rename("a/b/c", "1/2/3/c") == 0)
				c_count++;
			if (rename("1/2/3/c", "a/b/c") == 0)
				c_count++;
			if (c_count) {
				(void) strlcat(buf, "c_count: %d,", 256);
				(void) strlcat(buf, msg, 256);
				(void) fprintf(stderr, buf, c_count);
			}
		}
		break;
	default:
		while (i > 0) {
			int p_count = 0;
			if (rename("1", "a/b/c/d/e/1") == 0)
				p_count++;
			if (rename("a/b/c/d/e/1", "1") == 0)
				p_count++;
			if (p_count) {
				(void) strlcat(buf, "p_count: %d,", 256);
				(void) strlcat(buf, msg, 256);
				(void) fprintf(stderr, buf, p_count);
			}
		}
		break;
	}
	return (0);
}