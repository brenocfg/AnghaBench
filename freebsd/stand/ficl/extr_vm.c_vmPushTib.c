#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* cp; char* end; scalar_t__ index; } ;
struct TYPE_6__ {TYPE_1__ tib; } ;
typedef  TYPE_1__ TIB ;
typedef  TYPE_2__ FICL_VM ;
typedef  int FICL_INT ;

/* Variables and functions */

void vmPushTib(FICL_VM *pVM, char *text, FICL_INT nChars, TIB *pSaveTib)
{
    if (pSaveTib)
    {
        *pSaveTib = pVM->tib;
    }

    pVM->tib.cp = text;
    pVM->tib.end = text + nChars;
    pVM->tib.index = 0;
}