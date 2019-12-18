#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ count; int /*<<< orphan*/  text; } ;
struct TYPE_8__ {scalar_t__ pad; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ FICL_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  VM_QUIT ; 
 int chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmGetString (TYPE_1__*,TYPE_2__*,char) ; 
 int /*<<< orphan*/  vmTextOut (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  vmThrow (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ficlChDir(FICL_VM *pVM)
{
    FICL_STRING *pFS = (FICL_STRING *)pVM->pad;
    vmGetString(pVM, pFS, '\n');
    if (pFS->count > 0)
    {
       int err = chdir(pFS->text);
       if (err)
        {
            vmTextOut(pVM, "Error: path not found", 1);
            vmThrow(pVM, VM_QUIT);
        }
    }
    else
    {
        vmTextOut(pVM, "Warning (chdir): nothing happened", 1);
    }
    return;
}