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
typedef  int /*<<< orphan*/  Command ;

/* Variables and functions */
 scalar_t__ cmdtab ; 
 scalar_t__ cmdtab2 ; 
 scalar_t__ genget (char*,char**,int) ; 

__attribute__((used)) static Command
*getcmd(char *name)
{
    Command *cm;

    if ((cm = (Command *) genget(name, (char **) cmdtab, sizeof(Command))))
	return cm;
    return (Command *) genget(name, (char **) cmdtab2, sizeof(Command));
}