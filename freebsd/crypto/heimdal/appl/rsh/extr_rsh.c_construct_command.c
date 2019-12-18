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
 int /*<<< orphan*/  errx (int,char*,unsigned long) ; 
 char* malloc (size_t) ; 
 size_t max (int,size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static size_t
construct_command (char **res, int argc, char **argv)
{
    int i;
    size_t len = 0;
    char *tmp;

    for (i = 0; i < argc; ++i)
	len += strlen(argv[i]) + 1;
    len = max (1, len);
    tmp = malloc (len);
    if (tmp == NULL)
	errx (1, "malloc %lu failed", (unsigned long)len);

    *tmp = '\0';
    for (i = 0; i < argc - 1; ++i) {
	strlcat (tmp, argv[i], len);
	strlcat (tmp, " ", len);
    }
    if (argc > 0)
	strlcat (tmp, argv[argc-1], len);
    *res = tmp;
    return len;
}