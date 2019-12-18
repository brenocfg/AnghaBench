#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum fore200e_aal { ____Placeholder_fore200e_aal } fore200e_aal ;

/* Variables and functions */
#define  ATM_AAL0 132 
#define  ATM_AAL1 131 
#define  ATM_AAL2 130 
#define  ATM_AAL34 129 
#define  ATM_AAL5 128 
 int EINVAL ; 
 int FORE200E_AAL0 ; 
 int FORE200E_AAL34 ; 
 int FORE200E_AAL5 ; 

__attribute__((used)) static enum fore200e_aal
fore200e_atm2fore_aal(int aal)
{
    switch(aal) {
    case ATM_AAL0:  return FORE200E_AAL0;
    case ATM_AAL34: return FORE200E_AAL34;
    case ATM_AAL1:
    case ATM_AAL2:
    case ATM_AAL5:  return FORE200E_AAL5;
    }

    return -EINVAL;
}