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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char const*) ; 
 char* get_field (char**,size_t*,int*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
get_str(char **line, size_t *len, char **v, const char *name, int minlen,
    const char *filename, int lineno)
{
	int fieldlen;
	char *ptr;

	ptr = get_field(line, len, &fieldlen);
	if (ptr == NULL)
		return (1);
	if (fieldlen < minlen) {
		fprintf(stderr, "%s:%d too short %s\n", filename, lineno, name);
		return (1);
	}
	if ((*v = malloc(fieldlen + 1)) == NULL) {
		perror("malloc()");
		return (1);
	}
	memcpy(*v, ptr, fieldlen);
	(*v)[fieldlen] = '\0';

	return (0);
}