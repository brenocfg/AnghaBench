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
 int MODE_ECHO ; 
 int MODE_EDIT ; 
 int MODE_FORCE ; 
 int /*<<< orphan*/  TELOPT_ENCRYPT ; 
 int /*<<< orphan*/  TerminalNewMode (int) ; 
 int /*<<< orphan*/  encrypt_output ; 
 int /*<<< orphan*/  encrypt_request_end () ; 
 int /*<<< orphan*/  encrypt_request_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getconnmode () ; 
 scalar_t__ my_want_state_is_will (int /*<<< orphan*/ ) ; 

void
setconnmode(int force)
{
#ifdef	ENCRYPTION
    static int enc_passwd = 0;
#endif	/* ENCRYPTION */
    int newmode;

    newmode = getconnmode()|(force?MODE_FORCE:0);

    TerminalNewMode(newmode);

#ifdef  ENCRYPTION
    if ((newmode & (MODE_ECHO|MODE_EDIT)) == MODE_EDIT) {
	if (my_want_state_is_will(TELOPT_ENCRYPT)
				&& (enc_passwd == 0) && !encrypt_output) {
	    encrypt_request_start(0, 0);
	    enc_passwd = 1;
	}
    } else {
	if (enc_passwd) {
	    encrypt_request_end();
	    enc_passwd = 0;
	}
    }
#endif	/* ENCRYPTION */

}