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
 int lmpid ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  top_clear () ; 

void
i_loadave(int mpid, double avenrun[])
{
    int i;

    /* i_loadave also clears the screen, since it is first */
    top_clear();

    /* mpid == -1 implies this system doesn't have an _mpid */
    if (mpid != -1)
    {
	printf("last pid: %5d;  ", mpid);
    }

    printf("load averages");

    for (i = 0; i < 3; i++)
    {
	printf("%c %5.2f",
	    i == 0 ? ':' : ',',
	    avenrun[i]);
    }
    lmpid = mpid;
}