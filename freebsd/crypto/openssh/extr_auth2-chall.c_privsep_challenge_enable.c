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
typedef  int /*<<< orphan*/  KbdintDevice ;

/* Variables and functions */
 int /*<<< orphan*/ ** devices ; 

void
privsep_challenge_enable(void)
{
#if defined(BSD_AUTH) || defined(USE_PAM)
	int n = 0;
#endif
#ifdef BSD_AUTH
	extern KbdintDevice mm_bsdauth_device;
#endif
#ifdef USE_PAM
	extern KbdintDevice mm_sshpam_device;
#endif

#ifdef BSD_AUTH
	devices[n++] = &mm_bsdauth_device;
#else
#ifdef USE_PAM
	devices[n++] = &mm_sshpam_device;
#endif
#endif
}