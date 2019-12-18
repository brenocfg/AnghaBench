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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ encrypt_output ; 
 int /*<<< orphan*/  encrypt_send_end () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void
fatal(int f, const char *msg)
{
	char buf[BUFSIZ];

	(void) snprintf(buf, sizeof(buf), "telnetd: %s.\r\n", msg);
#ifdef	ENCRYPTION
	if (encrypt_output) {
		/*
		 * Better turn off encryption first....
		 * Hope it flushes...
		 */
		encrypt_send_end();
		netflush();
	}
#endif	/* ENCRYPTION */
	(void) write(f, buf, (int)strlen(buf));
	sleep(1);	/*XXX*/
	exit(1);
}