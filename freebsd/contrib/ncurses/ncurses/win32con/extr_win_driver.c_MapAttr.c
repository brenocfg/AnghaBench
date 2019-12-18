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
typedef  int attr_t ;
typedef  int WORD ;
struct TYPE_2__ {int* pairs; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  int /*<<< orphan*/  SCREEN ;

/* Variables and functions */
 int A_BOLD ; 
 int A_COLOR ; 
 int A_DIM ; 
 int A_REVERSE ; 
 int A_STANDOUT ; 
 int /*<<< orphan*/  AssertTCB () ; 
 int BACKGROUND_INTENSITY ; 
 int FOREGROUND_INTENSITY ; 
 int NUMPAIRS ; 
 int PairNumber (int) ; 
 TYPE_1__* PropOf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSP () ; 

__attribute__((used)) static WORD
MapAttr(TERMINAL_CONTROL_BLOCK * TCB, WORD res, attr_t ch)
{
    if (ch & A_COLOR) {
	int p;
	SCREEN *sp;

	AssertTCB();
	SetSP();
	p = PairNumber(ch);
	if (p > 0 && p < NUMPAIRS && TCB != 0 && sp != 0) {
	    WORD a;
	    a = PropOf(TCB)->pairs[p];
	    res = (res & 0xff00) | a;
	}
    }

    if (ch & A_REVERSE)
	res = ((res & 0xff00) | (((res & 0x07) << 4) | ((res & 0x70) >> 4)));

    if (ch & A_STANDOUT)
	res = ((res & 0xff00) | (((res & 0x07) << 4) | ((res & 0x70) >> 4))
	       | BACKGROUND_INTENSITY);

    if (ch & A_BOLD)
	res |= FOREGROUND_INTENSITY;

    if (ch & A_DIM)
	res |= BACKGROUND_INTENSITY;

    return res;
}