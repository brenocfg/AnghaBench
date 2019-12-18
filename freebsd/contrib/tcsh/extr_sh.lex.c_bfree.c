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
 int BUFSIZE ; 
 int /*<<< orphan*/  blkcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cantell ; 
 int fblocks ; 
 int /*<<< orphan*/ * fbuf ; 
 int feobp ; 
 int fseekp ; 
 scalar_t__ whyles ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfree(void)
{
    int sb, i;

    if (cantell)
	return;
    if (whyles)
	return;
    sb = (int) (fseekp - 1) / BUFSIZE;
    if (sb > 0) {
	for (i = 0; i < sb; i++)
	    xfree(fbuf[i]);
	(void) blkcpy(fbuf, &fbuf[sb]);
	fseekp -= BUFSIZE * sb;
	feobp -= BUFSIZE * sb;
	fblocks -= sb;
    }
}