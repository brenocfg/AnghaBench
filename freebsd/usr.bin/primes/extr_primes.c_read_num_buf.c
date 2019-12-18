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
typedef  int /*<<< orphan*/  ubig ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int LINE_MAX ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ isblank (char) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strtoumax (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ubig
read_num_buf(void)
{
	ubig val;
	char *p, buf[LINE_MAX];		/* > max number of digits. */

	for (;;) {
		if (fgets(buf, sizeof(buf), stdin) == NULL) {
			if (ferror(stdin))
				err(1, "stdin");
			exit(0);
		}
		for (p = buf; isblank(*p); ++p);
		if (*p == '\n' || *p == '\0')
			continue;
		if (*p == '-')
			errx(1, "negative numbers aren't permitted.");
		errno = 0;
		val = strtoumax(buf, &p, 0);
		if (errno)
			err(1, "%s", buf);
		if (*p != '\n')
			errx(1, "%s: illegal numeric format.", buf);
		return (val);
	}
}