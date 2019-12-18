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
 int CMD_BUF_LEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  history_add (char*) ; 

__attribute__((used)) static void history_read(const char *fname)
{
	FILE *f;
	char buf[CMD_BUF_LEN], *pos;

	f = fopen(fname, "r");
	if (f == NULL)
		return;

	while (fgets(buf, CMD_BUF_LEN, f)) {
		for (pos = buf; *pos; pos++) {
			if (*pos == '\r' || *pos == '\n') {
				*pos = '\0';
				break;
			}
		}
		history_add(buf);
	}

	fclose(f);
}