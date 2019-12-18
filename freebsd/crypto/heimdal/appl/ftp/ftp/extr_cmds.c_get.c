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
 scalar_t__ TYPE_I ; 
 scalar_t__ curtype ; 
 int /*<<< orphan*/  getit (int,char**,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ restart_point ; 

void
get(int argc, char **argv)
{
    char *filemode;

    if (restart_point) {
	if (curtype == TYPE_I)
	    filemode = "r+wb";
	else
	    filemode = "r+w";
    } else {
	if (curtype == TYPE_I)
	    filemode = "wb";
	else
	    filemode = "w";
    }

    getit(argc, argv, 0, filemode);
}