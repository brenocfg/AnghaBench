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
struct TYPE_6__ {TYPE_1__* pFreeSRB; } ;
struct TYPE_5__ {struct TYPE_5__* pNextSRB; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PACB ;

/* Variables and functions */
 int splcam () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static PSRB
trm_GetSRB(PACB pACB)
{
	int	intflag;
	PSRB	pSRB;

	intflag = splcam();
    	pSRB = pACB->pFreeSRB;
	if (pSRB) {
		pACB->pFreeSRB = pSRB->pNextSRB;
		pSRB->pNextSRB = NULL;
	}
	splx(intflag);
    	return (pSRB);
}