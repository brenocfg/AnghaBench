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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ALLOWED ; 
 int BUFSIZ ; 
 int NOT_ALLOWED ; 
 int /*<<< orphan*/  _PATH_FTPUSERS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ match (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int
checkaccess(char *name)
{
#define ALLOWED		0
#define	NOT_ALLOWED	1
    FILE *fd;
    int allowed = ALLOWED;
    char *user, *perm, line[BUFSIZ];
    char *foo;

    fd = fopen(_PATH_FTPUSERS, "r");

    if(fd == NULL)
	return allowed;

    while (fgets(line, sizeof(line), fd) != NULL)  {
	foo = NULL;
	user = strtok_r(line, " \t\n", &foo);
	if (user == NULL || user[0] == '#')
	    continue;
	perm = strtok_r(NULL, " \t\n", &foo);
	if (match(user, name) == 0){
	    if(perm && strcmp(perm, "allow") == 0)
		allowed = ALLOWED;
	    else
		allowed = NOT_ALLOWED;
	    break;
	}
    }
    fclose(fd);
    return allowed;
}