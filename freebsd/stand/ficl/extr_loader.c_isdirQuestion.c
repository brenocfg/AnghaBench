#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_FALSE ; 
 int /*<<< orphan*/  FICL_TRUE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void isdirQuestion(FICL_VM *pVM)
{
    struct stat sb;
    FICL_INT flag;
    int fd;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 1);
#endif

    fd = stackPopINT(pVM->pStack);
    flag = FICL_FALSE;
    do {
        if (fd < 0)
            break;
        if (fstat(fd, &sb) < 0)
            break;
        if (!S_ISDIR(sb.st_mode))
            break;
        flag = FICL_TRUE;
    } while (0);
    stackPushINT(pVM->pStack, flag);
}