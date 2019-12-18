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
struct command {int dummy; } ;
typedef  char Char ;

/* Variables and functions */
 int ERR_MASK ; 
 int ERR_NAME ; 
 scalar_t__ Isdigit (char) ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  stderror (int) ; 
 scalar_t__ umask (int) ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void
doumask(Char **v, struct command *c)
{
    Char *cp = v[1];
    int i;

    USE(c);
    if (cp == 0) {
	i = (int)umask(0);
	(void) umask(i);
	xprintf("%o\n", i);
	return;
    }
    i = 0;
    while (Isdigit(*cp) && *cp != '8' && *cp != '9')
	i = i * 8 + *cp++ - '0';
    if (*cp || i < 0 || i > 0777)
	stderror(ERR_NAME | ERR_MASK);
    (void) umask(i);
}