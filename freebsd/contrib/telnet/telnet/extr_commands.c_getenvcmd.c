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
struct envlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ EnvList ; 
 scalar_t__ genget (char*,char**,int) ; 

__attribute__((used)) static struct envlist *
getenvcmd(char *name)
{
    return (struct envlist *)
		genget(name, (char **) EnvList, sizeof(struct envlist));
}