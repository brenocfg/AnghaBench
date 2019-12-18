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
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ alarmed ; 
 int /*<<< orphan*/  break_sequence () ; 
 int /*<<< orphan*/  chat_logf (char*,char*) ; 
 char* clean (char*,int) ; 
 scalar_t__ quiet ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_char (char) ; 

int
put_string(char *s)
{
    quiet = 0;
    s = clean(s, 1);

    if (verbose)
        chat_logf("send (%v)", quiet ? "??????" : s);

    alarm(timeout); alarmed = 0;

    while (*s) {
	char c = *s++;

	if (c != '\\') {
	    if (!write_char (c))
		return 0;
	    continue;
	}

	c = *s++;
	switch (c) {
	case 'd':
	    sleep(1);
	    break;

	case 'K':
	    break_sequence();
	    break;

	case 'p':
	    usleep(10000); 	/* 1/100th of a second (arg is microseconds) */
	    break;

	default:
	    if (!write_char (c))
		return 0;
	    break;
	}
    }

    alarm(0);
    alarmed = 0;
    return (1);
}