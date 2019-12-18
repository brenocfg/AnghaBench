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
 int BUFSIZ ; 
 int ENOMEM ; 
 int errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int find_var (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 char** realloc (char**,int) ; 
 char* strchr (char*,char) ; 
 size_t strcspn (char*,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int
read_env_file(FILE *F, char ***env, int *assigned)
{
    int idx = 0;
    int i;
    char **l;
    char buf[BUFSIZ], *p, *r;
    char **tmp;
    int ret = 0;

    *assigned = 0;

    for(idx = 0; *env != NULL && (*env)[idx] != NULL; idx++);
    l = *env;

    /* This is somewhat more relaxed on what it accepts then
     * Wietses sysv_environ from K4 was...
     */
    while (fgets(buf, BUFSIZ, F) != NULL) {
	buf[strcspn(buf, "#\n")] = '\0';

	for(p = buf; isspace((unsigned char)*p); p++);
	if (*p == '\0')
	    continue;

	/* Here one should check that it's a 'valid' env string... */
	r = strchr(p, '=');
	if (r == NULL)
	    continue;

	if((i = find_var(l, p, r - p + 1)) >= 0) {
	    char *val = strdup(p);
	    if(val == NULL) {
		ret = ENOMEM;
		break;
	    }
	    free(l[i]);
	    l[i] = val;
	    (*assigned)++;
	    continue;
	}

	tmp = realloc(l, (idx+2) * sizeof (char *));
	if(tmp == NULL) {
	    ret = ENOMEM;
	    break;
	}

	l = tmp;
	l[idx] = strdup(p);
	if(l[idx] == NULL) {
	    ret = ENOMEM;
	    break;
	}
	l[++idx] = NULL;
	(*assigned)++;
    }
    if(ferror(F))
	ret = errno;
    *env = l;
    return ret;
}