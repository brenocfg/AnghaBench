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
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  command_errbuf ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
fdt_merge_strings(int argc, char *argv[], int start, char **buffer)
{
	char *buf;
	int i, idx, sz;

	*buffer = NULL;
	sz = 0;

	for (i = start; i < argc; i++)
		sz += strlen(argv[i]);

	/* Additional bytes for whitespaces between args */
	sz += argc - start;

	buf = (char *)malloc(sizeof(char) * sz);
	if (buf == NULL) {
		sprintf(command_errbuf, "could not allocate space "
		    "for string");
		return (1);
	}
	bzero(buf, sizeof(char) * sz);

	idx = 0;
	for (i = start, idx = 0; i < argc; i++) {
		strcpy(buf + idx, argv[i]);
		idx += strlen(argv[i]);
		buf[idx] = ' ';
		idx++;
	}
	buf[sz - 1] = '\0';
	*buffer = buf;
	return (0);
}