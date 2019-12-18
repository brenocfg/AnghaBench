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
struct TYPE_3__ {scalar_t__ textOut; } ;
typedef  scalar_t__ OUTFUNC ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 scalar_t__ ficlTextOut ; 

void vmSetTextOut(FICL_VM *pVM, OUTFUNC textOut)
{
    if (textOut)
        pVM->textOut = textOut;
    else
        pVM->textOut = ficlTextOut;

    return;
}