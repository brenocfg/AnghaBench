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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static char *
get_line(FILE *b, size_t *n)
{
	char *cp;
	size_t len;
	static char *buf;
	static size_t bufsize;

	if ((cp = fgetln(b, &len)) == NULL)
		return (NULL);

	if (cp[len - 1] != '\n')
		len++;
	if (len + 1 > bufsize) {
		do {
			bufsize += 1024;
		} while (len + 1 > bufsize);
		if ((buf = realloc(buf, bufsize)) == NULL)
			err(EXIT_FAILURE, NULL);
	}
	memcpy(buf, cp, len - 1);
	buf[len - 1] = '\n';
	buf[len] = '\0';
	if (n != NULL)
		*n = len;
	return (buf);
}