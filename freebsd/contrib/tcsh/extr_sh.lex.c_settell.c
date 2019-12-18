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
typedef  int off_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  L_INCR ; 
 int /*<<< orphan*/  SHIN ; 
 scalar_t__ arginp ; 
 int cantell ; 
 int fblocks ; 
 int fbobp ; 
 void** fbuf ; 
 int feobp ; 
 int fseekp ; 
 scalar_t__ intty ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ onelflg ; 
 void* xcalloc (int,int) ; 

void
settell(void)
{
    off_t x;
    cantell = 0;
    if (arginp || onelflg || intty)
	return;
    if ((x = lseek(SHIN, (off_t) 0, L_INCR)) == -1)
	return;
    fbuf = xcalloc(2, sizeof(Char **));
    fblocks = 1;
    fbuf[0] = xcalloc(BUFSIZE, sizeof(Char));
    fseekp = fbobp = feobp = x;
    cantell = 1;
}