#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  fun; } ;
struct TYPE_4__ {int len; int* buf; } ;
typedef  int Char ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 size_t A_K_DN ; 
 size_t A_K_EN ; 
 size_t A_K_HO ; 
 size_t A_K_LT ; 
 size_t A_K_RT ; 
 size_t A_K_UP ; 
 int /*<<< orphan*/  AddXkey (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int CTL_ESC (char) ; 
 scalar_t__ VImode ; 
 TYPE_2__* arrow ; 

void
DefaultArrowKeys(void)
{
    static Char strA[] = {033, '[', 'A', '\0'};
    static Char strB[] = {033, '[', 'B', '\0'};
    static Char strC[] = {033, '[', 'C', '\0'};
    static Char strD[] = {033, '[', 'D', '\0'};
    static Char strH[] = {033, '[', 'H', '\0'};
    static Char strF[] = {033, '[', 'F', '\0'};
    static Char stOA[] = {033, 'O', 'A', '\0'};
    static Char stOB[] = {033, 'O', 'B', '\0'};
    static Char stOC[] = {033, 'O', 'C', '\0'};
    static Char stOD[] = {033, 'O', 'D', '\0'};
    static Char stOH[] = {033, 'O', 'H', '\0'};
    static Char stOF[] = {033, 'O', 'F', '\0'};

    CStr cs;
#ifndef IS_ASCII
    if (strA[0] == 033)
    {
	strA[0] = CTL_ESC('\033');
	strB[0] = CTL_ESC('\033');
	strC[0] = CTL_ESC('\033');
	strD[0] = CTL_ESC('\033');
	strH[0] = CTL_ESC('\033');
	strF[0] = CTL_ESC('\033');
	stOA[0] = CTL_ESC('\033');
	stOB[0] = CTL_ESC('\033');
	stOC[0] = CTL_ESC('\033');
	stOD[0] = CTL_ESC('\033');
	stOH[0] = CTL_ESC('\033');
	stOF[0] = CTL_ESC('\033');
    }
#endif

    cs.len = 3;

    cs.buf = strA; AddXkey(&cs, &arrow[A_K_UP].fun, arrow[A_K_UP].type);
    cs.buf = strB; AddXkey(&cs, &arrow[A_K_DN].fun, arrow[A_K_DN].type);
    cs.buf = strC; AddXkey(&cs, &arrow[A_K_RT].fun, arrow[A_K_RT].type);
    cs.buf = strD; AddXkey(&cs, &arrow[A_K_LT].fun, arrow[A_K_LT].type);
    cs.buf = strH; AddXkey(&cs, &arrow[A_K_HO].fun, arrow[A_K_HO].type);
    cs.buf = strF; AddXkey(&cs, &arrow[A_K_EN].fun, arrow[A_K_EN].type);
    cs.buf = stOA; AddXkey(&cs, &arrow[A_K_UP].fun, arrow[A_K_UP].type);
    cs.buf = stOB; AddXkey(&cs, &arrow[A_K_DN].fun, arrow[A_K_DN].type);
    cs.buf = stOC; AddXkey(&cs, &arrow[A_K_RT].fun, arrow[A_K_RT].type);
    cs.buf = stOD; AddXkey(&cs, &arrow[A_K_LT].fun, arrow[A_K_LT].type);
    cs.buf = stOH; AddXkey(&cs, &arrow[A_K_HO].fun, arrow[A_K_HO].type);
    cs.buf = stOF; AddXkey(&cs, &arrow[A_K_EN].fun, arrow[A_K_EN].type);

    if (VImode) {
	cs.len = 2;
	cs.buf = &strA[1]; AddXkey(&cs, &arrow[A_K_UP].fun, arrow[A_K_UP].type);
	cs.buf = &strB[1]; AddXkey(&cs, &arrow[A_K_DN].fun, arrow[A_K_DN].type);
	cs.buf = &strC[1]; AddXkey(&cs, &arrow[A_K_RT].fun, arrow[A_K_RT].type);
	cs.buf = &strD[1]; AddXkey(&cs, &arrow[A_K_LT].fun, arrow[A_K_LT].type);
	cs.buf = &strH[1]; AddXkey(&cs, &arrow[A_K_HO].fun, arrow[A_K_HO].type);
	cs.buf = &strF[1]; AddXkey(&cs, &arrow[A_K_EN].fun, arrow[A_K_EN].type);
	cs.buf = &stOA[1]; AddXkey(&cs, &arrow[A_K_UP].fun, arrow[A_K_UP].type);
	cs.buf = &stOB[1]; AddXkey(&cs, &arrow[A_K_DN].fun, arrow[A_K_DN].type);
	cs.buf = &stOC[1]; AddXkey(&cs, &arrow[A_K_RT].fun, arrow[A_K_RT].type);
	cs.buf = &stOD[1]; AddXkey(&cs, &arrow[A_K_LT].fun, arrow[A_K_LT].type);
	cs.buf = &stOH[1]; AddXkey(&cs, &arrow[A_K_HO].fun, arrow[A_K_HO].type);
	cs.buf = &stOF[1]; AddXkey(&cs, &arrow[A_K_EN].fun, arrow[A_K_EN].type);
    }
}