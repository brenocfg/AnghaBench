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
struct varent {scalar_t__* vec; } ;
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_NOMORE ; 
 int /*<<< orphan*/ * STRargv ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 struct varent* adrof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lshift (scalar_t__*,int) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  strip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udvar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_vars (int /*<<< orphan*/ *) ; 

void
shift(Char **v, struct command *c)
{
    struct varent *argv;
    Char *name;

    USE(c);
    v++;
    name = *v;
    if (name == 0)
	name = STRargv;
    else
	(void) strip(name);
    argv = adrof(name);
    if (argv == NULL || argv->vec == NULL)
	udvar(name);
    if (argv->vec[0] == 0)
	stderror(ERR_NAME | ERR_NOMORE);
    lshift(argv->vec, 1);
    update_vars(name);
}