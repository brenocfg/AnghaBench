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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  local_host ;

/* Variables and functions */
 int /*<<< orphan*/  Exit (int) ; 
 int MODE_TRAPSIG ; 
 int Scheduler (int) ; 
 int /*<<< orphan*/  TELOPT_AUTHENTICATION ; 
 int /*<<< orphan*/  TELOPT_ENCRYPT ; 
 int /*<<< orphan*/  TELOPT_LFLOW ; 
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 int /*<<< orphan*/  TELOPT_NAWS ; 
 int /*<<< orphan*/  TELOPT_NEW_ENVIRON ; 
 int /*<<< orphan*/  TELOPT_SGA ; 
 int /*<<< orphan*/  TELOPT_STATUS ; 
 int /*<<< orphan*/  TELOPT_TSPEED ; 
 int /*<<< orphan*/  TELOPT_TTYPE ; 
 int /*<<< orphan*/  TELOPT_XDISPLOC ; 
 int /*<<< orphan*/  TerminalNewMode (int) ; 
 int /*<<< orphan*/  auth_encrypt_init (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_encrypt_user (char*) ; 
 scalar_t__ auth_has_failed ; 
 scalar_t__ autologin ; 
 scalar_t__ binary ; 
 scalar_t__ encrypt_is_encrypting () ; 
 scalar_t__ env_getvalue (unsigned char*) ; 
 int getconnmode () ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  hostname ; 
 scalar_t__ intr_happened ; 
 int intr_waiting ; 
 scalar_t__ my_want_state_is_dont (int /*<<< orphan*/ ) ; 
 scalar_t__ my_want_state_is_wont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  send_do (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_will (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setcommandmode () ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_telnet_init () ; 
 int /*<<< orphan*/  tel_enter_binary (scalar_t__) ; 
 scalar_t__ telnet_spin () ; 
 scalar_t__ telnetport ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int wantencryption ; 

void
my_telnet(char *user)
{
    int printed_encrypt = 0;

    sys_telnet_init();

#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
    {
	static char local_host[256] = { 0 };

	if (!local_host[0]) {
		/* XXX - should be k_gethostname? */
		gethostname(local_host, sizeof(local_host));
		local_host[sizeof(local_host)-1] = 0;
	}
	auth_encrypt_init(local_host, hostname, "TELNET", 0);
	auth_encrypt_user(user);
    }
#endif
    if (telnetport) {
#if	defined(AUTHENTICATION)
	if (autologin)
		send_will(TELOPT_AUTHENTICATION, 1);
#endif
#if	defined(ENCRYPTION)
	send_do(TELOPT_ENCRYPT, 1);
	send_will(TELOPT_ENCRYPT, 1);
#endif
	send_do(TELOPT_SGA, 1);
	send_will(TELOPT_TTYPE, 1);
	send_will(TELOPT_NAWS, 1);
	send_will(TELOPT_TSPEED, 1);
	send_will(TELOPT_LFLOW, 1);
	send_will(TELOPT_LINEMODE, 1);
	send_will(TELOPT_NEW_ENVIRON, 1);
	send_do(TELOPT_STATUS, 1);
	if (env_getvalue((unsigned char *)"DISPLAY"))
	    send_will(TELOPT_XDISPLOC, 1);
	if (binary)
	    tel_enter_binary(binary);
    }

#ifdef ENCRYPTION
    /*
     * Note: we assume a tie to the authentication option here.  This
     * is necessary so that authentication fails, we don't spin
     * forever.
     */
    if (telnetport && wantencryption) {
	time_t timeout = time(0) + 60;

	send_do(TELOPT_ENCRYPT, 1);
	send_will(TELOPT_ENCRYPT, 1);
	while (1) {
	    if (my_want_state_is_wont(TELOPT_AUTHENTICATION)) {
		if (wantencryption == -1) {
		    break;
		} else {
		    printf("\nServer refused to negotiate authentication,\n");
		    printf("which is required for encryption.\n");
		    Exit(1);
		}
	    }
	    if (auth_has_failed) {
		printf("\nAuthentication negotiation has failed,\n");
		printf("which is required for encryption.\n");
		Exit(1);
	    }
	    if (my_want_state_is_dont(TELOPT_ENCRYPT) ||
		my_want_state_is_wont(TELOPT_ENCRYPT)) {
		printf("\nServer refused to negotiate encryption.\n");
		Exit(1);
	    }
	    if (encrypt_is_encrypting())
		break;
	    if (time(0) > timeout) {
		printf("\nEncryption could not be enabled.\n");
		Exit(1);
	    }
	    if (printed_encrypt == 0) {
		    printed_encrypt = 1;
		    printf("Waiting for encryption to be negotiated...\n");
		    /*
		     * Turn on MODE_TRAPSIG and then turn off localchars
		     * so that ^C will cause telnet to exit.
		     */
		    TerminalNewMode(getconnmode()|MODE_TRAPSIG);
		    intr_waiting = 1;
	    }
	    if (intr_happened) {
		    printf("\nUser interrupt.\n");
		    Exit(1);
	    }
	    if (telnet_spin()) {
		    printf("\nServer disconnected.\n");
		    Exit(1);
	    }

	}
	if (printed_encrypt) {
		printf("Encryption negotiated.\n");
		intr_waiting = 0;
		setconnmode(0);
	}
    }
#endif

    for (;;) {
	int schedValue;

	while ((schedValue = Scheduler(0)) != 0) {
	    if (schedValue == -1) {
		setcommandmode();
		return;
	    }
	}

	if (Scheduler(1) == -1) {
	    setcommandmode();
	    return;
	}
    }
}