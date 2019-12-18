#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  keylist ;
typedef  int WORD ;
struct TYPE_2__ {int /*<<< orphan*/  rmap; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  int /*<<< orphan*/  SCREEN ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int FALSE ; 
 scalar_t__ FKEYS ; 
 int /*<<< orphan*/  GenMap (int /*<<< orphan*/ ,int) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ N_INI ; 
 TYPE_1__* PropOf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSP () ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 void* bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  returnCode (int) ; 
 int /*<<< orphan*/  rkeycompare ; 

__attribute__((used)) static bool
drv_kyExist(TERMINAL_CONTROL_BLOCK * TCB, int keycode)
{
    SCREEN *sp;
    WORD nKey;
    void *res;
    bool found = FALSE;
    LONG key = GenMap(0, (WORD) keycode);

    AssertTCB();
    SetSP();

    AssertTCB();

    T((T_CALLED("win32con::drv_kyExist(%p, %d)"), TCB, keycode));
    res = bsearch(&key,
		  PropOf(TCB)->rmap,
		  (size_t) (N_INI + FKEYS),
		  sizeof(keylist[0]),
		  rkeycompare);
    if (res) {
	key = *((LONG *) res);
	nKey = LOWORD(key);
	if (!(nKey & 0x8000))
	    found = TRUE;
    }
    returnCode(found);
}