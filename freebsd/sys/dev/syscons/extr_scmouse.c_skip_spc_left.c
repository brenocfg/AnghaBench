#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int xsize; int /*<<< orphan*/  vtb; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SPACE_CHAR (int) ; 
 int sc_vtb_getc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
skip_spc_left(scr_stat *scp, int p)
{
    int c;
    int i;

    for (i = p-- % scp->xsize - 1; i >= 0; --i) {
	c = sc_vtb_getc(&scp->vtb, p);
	if (!IS_SPACE_CHAR(c))
	    break;
	--p;
    }
    return i;
}