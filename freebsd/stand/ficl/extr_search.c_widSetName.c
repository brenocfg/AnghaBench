#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* p; } ;
struct TYPE_3__ {char* name; } ;
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  TYPE_1__ FICL_HASH ;

/* Variables and functions */
 TYPE_2__ vmPop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void widSetName(FICL_VM *pVM)
{
    char *cp = (char *)vmPop(pVM).p;
    FICL_HASH *pHash = vmPop(pVM).p;
    pHash->name = cp;
    return;
}