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
 int LINUX_SI_ASYNCIO ; 
 int LINUX_SI_KERNEL ; 
 int LINUX_SI_MESGQ ; 
 int LINUX_SI_QUEUE ; 
 int LINUX_SI_TIMER ; 
 int LINUX_SI_TKILL ; 
 int LINUX_SI_USER ; 
#define  SI_ASYNCIO 134 
#define  SI_KERNEL 133 
#define  SI_LWP 132 
#define  SI_MESGQ 131 
#define  SI_QUEUE 130 
#define  SI_TIMER 129 
#define  SI_USER 128 

__attribute__((used)) static void
sicode_to_lsicode(int si_code, int *lsi_code)
{

	switch (si_code) {
	case SI_USER:
		*lsi_code = LINUX_SI_USER;
		break;
	case SI_KERNEL:
		*lsi_code = LINUX_SI_KERNEL;
		break;
	case SI_QUEUE:
		*lsi_code = LINUX_SI_QUEUE;
		break;
	case SI_TIMER:
		*lsi_code = LINUX_SI_TIMER;
		break;
	case SI_MESGQ:
		*lsi_code = LINUX_SI_MESGQ;
		break;
	case SI_ASYNCIO:
		*lsi_code = LINUX_SI_ASYNCIO;
		break;
	case SI_LWP:
		*lsi_code = LINUX_SI_TKILL;
		break;
	default:
		*lsi_code = si_code;
		break;
	}
}