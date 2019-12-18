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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  blkcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int fblocks ; 
 int /*<<< orphan*/ ** fbuf ; 
 void* xcalloc (int,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
balloc(int buf)
{
    Char **nfbuf;

    while (buf >= fblocks) {
	nfbuf = xcalloc(fblocks + 2, sizeof(Char **));
	if (fbuf) {
	    (void) blkcpy(nfbuf, fbuf);
	    xfree(fbuf);
	}
	fbuf = nfbuf;
	fbuf[fblocks] = xcalloc(BUFSIZE, sizeof(Char));
	fblocks++;
    }
}