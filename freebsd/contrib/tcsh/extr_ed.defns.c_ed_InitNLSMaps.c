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

/* Variables and functions */
 scalar_t__ AsciiOnly ; 
 size_t CTL_ESC (int) ; 
 int /*<<< orphan*/ * CcKeyMap ; 
 int /*<<< orphan*/  F_INSERT ; 
 scalar_t__ Isprint (size_t) ; 
 int NLSMapsAreInited ; 
 scalar_t__ NoNLSRebind ; 

void
ed_InitNLSMaps(void)
{
    int i;

    if (AsciiOnly)
	return;
    if (NoNLSRebind)
	return;
    for (i = 0200; i <= 0377; i++) {
	if (Isprint(CTL_ESC(i))) {
	    CcKeyMap[CTL_ESC(i)] = F_INSERT;
	}
    }
    NLSMapsAreInited = 1;
}