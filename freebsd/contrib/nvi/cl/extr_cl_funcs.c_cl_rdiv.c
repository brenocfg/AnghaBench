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
struct TYPE_3__ {int /*<<< orphan*/  rows; scalar_t__ coff; scalar_t__ cols; int /*<<< orphan*/  roff; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 char ACS_VLINE ; 
 int /*<<< orphan*/  mvvline (int /*<<< orphan*/ ,scalar_t__,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cl_rdiv(SCR *sp)
{
#ifdef __NetBSD__
	mvvline(sp->roff, sp->cols + sp->coff, '|', sp->rows);
#else
	mvvline(sp->roff, sp->cols + sp->coff, ACS_VLINE, sp->rows);
#endif
}