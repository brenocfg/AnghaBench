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

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
simple_readline(char *prompt)
{
    char buf[BUFSIZ];
    printf ("%s", prompt);
    fflush (stdout);
    if(fgets(buf, sizeof(buf), stdin) == NULL)
	return NULL;
    if (buf[strlen(buf) - 1] == '\n')
	buf[strlen(buf) - 1] = '\0';
    return strdup(buf);
}