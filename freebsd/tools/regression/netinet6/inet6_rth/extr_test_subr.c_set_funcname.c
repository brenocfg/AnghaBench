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
 size_t FUNCNAMESIZE ; 
 int /*<<< orphan*/  g_funcname ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,size_t) ; 

void
set_funcname(char *bufp, size_t bufsize)
{
	strlcpy(g_funcname, bufp,
	    bufsize < FUNCNAMESIZE ? bufsize : FUNCNAMESIZE);
}