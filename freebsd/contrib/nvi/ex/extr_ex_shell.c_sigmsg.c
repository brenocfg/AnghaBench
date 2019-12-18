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
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strsignal (int) ; 

__attribute__((used)) static const char *
sigmsg(int signo)
{
	static char buf[40];
	char *message;

	/* POSIX.1-2008 leaves strsignal(3)'s return value unspecified. */
	if ((message = strsignal(signo)) != NULL)
		return message;
	(void)snprintf(buf, sizeof(buf), "Unknown signal: %d", signo);
	return (buf);
}