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
 int ERR_COMMAND ; 
 int ERR_NAME ; 
 int ERR_STRING ; 
 scalar_t__ Vexpath ; 
 scalar_t__ exerr ; 
 scalar_t__ expath ; 
 int /*<<< orphan*/  setname (char*) ; 
 char* short2str (scalar_t__) ; 
 int /*<<< orphan*/  stderror (int,...) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
pexerr(void)
{
    /* Couldn't find the damn thing */
    if (expath) {
	setname(short2str(expath));
#ifdef VFORK
	Vexpath = 0;
#endif /* VFORK */
	xfree(expath);
	expath = 0;
    }
    else
	setname("");
    if (exerr)
	stderror(ERR_NAME | ERR_STRING, exerr);
    stderror(ERR_NAME | ERR_COMMAND);
}