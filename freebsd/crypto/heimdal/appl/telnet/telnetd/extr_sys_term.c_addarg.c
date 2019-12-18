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
struct arg_val {int size; int argc; int /*<<< orphan*/ ** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static void
addarg(struct arg_val *argv, const char *val)
{
    if(argv->size <= argv->argc+1) {
	argv->argv = realloc(argv->argv, sizeof(char*) * (argv->size + 10));
	if (argv->argv == NULL)
	    fatal (net, "realloc: out of memory");
	argv->size+=10;
    }
    if((argv->argv[argv->argc++] = strdup(val)) == NULL)
	fatal (net, "strdup: out of memory");
    argv->argv[argv->argc]   = NULL;
}