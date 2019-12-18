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
struct TYPE_6__ {int /*<<< orphan*/ * pForthWords; } ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_HASH ;

/* Variables and functions */
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* vmGetDict (TYPE_1__*) ; 

__attribute__((used)) static void forthWordlist(FICL_VM *pVM)
{
    FICL_HASH *pHash = vmGetDict(pVM)->pForthWords;
    stackPushPtr(pVM->pStack, pHash);
    return;
}