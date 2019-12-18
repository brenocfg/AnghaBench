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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
expand_one_file(FILE *f, const char *cell)
{
    static char buf[1024];
    char *p;

    while (fgets (buf, sizeof(buf), f) != NULL) {
	if(buf[0] == '>') {
	    for(p = buf; *p && !isspace((unsigned char)*p) && *p != '#'; p++)
		;
	    *p = '\0';
	    if(strncmp(buf + 1, cell, strlen(cell)) == 0)
		return buf + 1;
	}
	buf[0] = '\0';
    }
    return NULL;
}