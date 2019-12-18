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
struct msgbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msgbuf_addchar (struct msgbuf*,int) ; 
 int msgbuf_getchar (struct msgbuf*) ; 

void
msgbuf_copy(struct msgbuf *src, struct msgbuf *dst)
{
	int c;

	while ((c = msgbuf_getchar(src)) >= 0)
		msgbuf_addchar(dst, c);
}