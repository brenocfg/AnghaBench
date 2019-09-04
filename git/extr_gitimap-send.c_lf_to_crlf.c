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
struct strbuf {size_t len; char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,size_t,size_t) ; 
 char* xmallocz (size_t) ; 

__attribute__((used)) static void lf_to_crlf(struct strbuf *msg)
{
	char *new_msg;
	size_t i, j;
	char lastc;

	/* First pass: tally, in j, the size of the new_msg string: */
	for (i = j = 0, lastc = '\0'; i < msg->len; i++) {
		if (msg->buf[i] == '\n' && lastc != '\r')
			j++; /* a CR will need to be added here */
		lastc = msg->buf[i];
		j++;
	}

	new_msg = xmallocz(j);

	/*
	 * Second pass: write the new_msg string.  Note that this loop is
	 * otherwise identical to the first pass.
	 */
	for (i = j = 0, lastc = '\0'; i < msg->len; i++) {
		if (msg->buf[i] == '\n' && lastc != '\r')
			new_msg[j++] = '\r';
		lastc = new_msg[j++] = msg->buf[i];
	}
	strbuf_attach(msg, new_msg, j, j + 1);
}