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
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static int check_for_user(FILE *fp,const char *name)
{
    char *buffer;
    size_t len;
    int found = 0;

    len = strlen(name);
    if ((buffer = malloc(len+2)) == NULL)
	errx(EXIT_FAILURE, "virtual memory exhausted");

    while(fgets(buffer, len+2, fp) != NULL)
    {
	if ((strncmp(name, buffer, len) == 0) &&
	    (buffer[len] == '\n'))
	{
	    found = 1;
	    break;
	}
    }
    fclose(fp);
    free(buffer);
    return found;
}