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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SIGRETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/ * cout ; 
 int data ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ proxflag ; 
 int /*<<< orphan*/  pswitch (int) ; 
 int /*<<< orphan*/  sec_end () ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

RETSIGTYPE
lostpeer(int sig)
{

    if (connected) {
	if (cout != NULL) {
	    shutdown(fileno(cout), SHUT_RDWR);
	    fclose(cout);
	    cout = NULL;
	}
	if (data >= 0) {
	    shutdown(data, SHUT_RDWR);
	    close(data);
	    data = -1;
	}
	connected = 0;
    }
    pswitch(1);
    if (connected) {
	if (cout != NULL) {
	    shutdown(fileno(cout), SHUT_RDWR);
	    fclose(cout);
	    cout = NULL;
	}
	connected = 0;
    }
    proxflag = 0;
    pswitch(0);
    sec_end();
    SIGRETURN(0);
}