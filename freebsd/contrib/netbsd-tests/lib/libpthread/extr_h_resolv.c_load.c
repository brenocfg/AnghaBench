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
 int /*<<< orphan*/  WS ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  hosts ; 
 int /*<<< orphan*/  sl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
load(const char *fname)
{
	FILE *fp;
	size_t len;
	char *line;

	if ((fp = fopen(fname, "r")) == NULL)
		err(1, "Cannot open `%s'", fname);
	while ((line = fgetln(fp, &len)) != NULL) {
		char c = line[len];
		char *ptr;
		line[len] = '\0';
		for (ptr = strtok(line, WS); ptr; ptr = strtok(NULL, WS))
			sl_add(hosts, strdup(ptr));
		line[len] = c;
	}

	(void)fclose(fp);
}