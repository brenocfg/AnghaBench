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
 void* CONTROL (char) ; 
 scalar_t__ ISend ; 
 int /*<<< orphan*/  SB_CLEAR () ; 
 scalar_t__ SYNCHing ; 
 int /*<<< orphan*/  TS_DATA ; 
 int /*<<< orphan*/  _POSIX_VDISABLE ; 
 int /*<<< orphan*/  auth_encrypt_connect (scalar_t__) ; 
 scalar_t__ connected ; 
 scalar_t__ donebinarytoggle ; 
 void* echoc ; 
 int /*<<< orphan*/  env_init () ; 
 void* escape ; 
 int flushline ; 
 scalar_t__ localflow ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  options ; 
 int restartany ; 
 int /*<<< orphan*/  rlogin ; 
 int /*<<< orphan*/  telrcv_state ; 

void
init_telnet(void)
{
    env_init();

    SB_CLEAR();
    memset(options, 0, sizeof options);

    connected = ISend = localflow = donebinarytoggle = 0;
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
    auth_encrypt_connect(connected);
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION)  */
    restartany = -1;

    SYNCHing = 0;

    /* Don't change NetTrace */

    escape = CONTROL(']');
    rlogin = _POSIX_VDISABLE;
#ifdef	KLUDGELINEMODE
    echoc = CONTROL('E');
#endif

    flushline = 1;
    telrcv_state = TS_DATA;
}