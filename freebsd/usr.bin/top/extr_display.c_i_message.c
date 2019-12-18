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
 int /*<<< orphan*/  NEXT_MSG_ADDLEN ; 
 int /*<<< orphan*/  clear_eol (scalar_t__) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 scalar_t__ lastline ; 
 scalar_t__ msglen ; 
 char* next_msg ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  top_standout (char*) ; 
 scalar_t__ y_message ; 

void
i_message(void)
{
    next_msg = setup_buffer(next_msg, NEXT_MSG_ADDLEN);

    while (lastline < y_message)
    {
	fputc('\n', stdout);
	lastline++;
    }
    if (next_msg[0] != '\0')
    {
	top_standout(next_msg);
	msglen = strlen(next_msg);
	next_msg[0] = '\0';
    }
    else if (msglen > 0)
    {
	(void) clear_eol(msglen);
	msglen = 0;
    }
}