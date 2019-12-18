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

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,char const*,int /*<<< orphan*/ ,char,char*) ; 
 int /*<<< orphan*/ * symname ; 
 char** value ; 

__attribute__((used)) static void
debugsym(const char *why, int symind)
{
	debug("%s %s%c%s", why, symname[symind],
	    value[symind] ? '=' : ' ',
	    value[symind] ? value[symind] : "undef");
}