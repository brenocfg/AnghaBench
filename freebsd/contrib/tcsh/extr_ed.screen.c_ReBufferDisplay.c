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
 int /*<<< orphan*/ ** Display ; 
 int INBUFSIZE ; 
 int /*<<< orphan*/  T_co ; 
 int TermH ; 
 int TermV ; 
 int Val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** Vdisplay ; 
 int /*<<< orphan*/  blkfree (int /*<<< orphan*/ **) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static void
ReBufferDisplay(void)
{
    int i;
    Char **b;

    b = Display;
    Display = NULL;
    blkfree(b);
    b = Vdisplay;
    Vdisplay = NULL;
    blkfree(b);
    TermH = Val(T_co);
    TermV = (INBUFSIZE * 4) / TermH + 1;/*FIXBUF*/
    b = xmalloc(sizeof(*b) * (TermV + 1));
    for (i = 0; i < TermV; i++)
	b[i] = xmalloc(sizeof(*b[i]) * (TermH + 1));
    b[TermV] = NULL;
    Display = b;
    b = xmalloc(sizeof(*b) * (TermV + 1));
    for (i = 0; i < TermV; i++)
	b[i] = xmalloc(sizeof(*b[i]) * (TermH + 1));
    b[TermV] = NULL;
    Vdisplay = b;
}