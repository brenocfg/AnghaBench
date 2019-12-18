#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i; } ;
struct TYPE_5__ {scalar_t__ index; int /*<<< orphan*/ * end; int /*<<< orphan*/ * cp; } ;
struct TYPE_7__ {char* pad; TYPE_2__ sourceID; TYPE_1__ tib; int /*<<< orphan*/  state; int /*<<< orphan*/ * runningWord; int /*<<< orphan*/ * ip; scalar_t__ fRestart; int /*<<< orphan*/  rStack; } ;
typedef  TYPE_3__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  INTERPRET ; 
 int /*<<< orphan*/  stackReset (int /*<<< orphan*/ ) ; 

void vmQuit(FICL_VM *pVM)
{
    stackReset(pVM->rStack);
    pVM->fRestart    = 0;
    pVM->ip          = NULL;
    pVM->runningWord = NULL;
    pVM->state       = INTERPRET;
    pVM->tib.cp      = NULL;
    pVM->tib.end     = NULL;
    pVM->tib.index   = 0;
    pVM->pad[0]      = '\0';
    pVM->sourceID.i  = 0;
    return;
}