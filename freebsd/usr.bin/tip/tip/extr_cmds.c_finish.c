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
 int /*<<< orphan*/  DISCONNECT ; 
 int /*<<< orphan*/  FD ; 
 char* NOSTR ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  tipabort (char*) ; 
 char* value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
finish(int c)
{
	char *dismsg;

	if ((dismsg = value(DISCONNECT)) != NOSTR) {
		write(FD, dismsg, strlen(dismsg));
		sleep(5);
	}
	tipabort(NOSTR);
}