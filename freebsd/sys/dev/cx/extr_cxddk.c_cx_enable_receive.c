#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num; scalar_t__ mode; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR_DISRX ; 
 int /*<<< orphan*/  CCR_ENRX ; 
 int /*<<< orphan*/  IER (int /*<<< orphan*/ ) ; 
 unsigned char IER_RET ; 
 unsigned char IER_RXD ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  cx_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cx_receive_enabled (TYPE_1__*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

void cx_enable_receive (cx_chan_t *c, int on)
{
	unsigned char ier;

	if (cx_receive_enabled(c) && ! on) {
		outb (CAR(c->port), c->num & 3);
		if (c->mode == M_ASYNC) {
			ier = inb (IER(c->port));
			outb (IER(c->port), ier & ~ (IER_RXD | IER_RET));
		}
		cx_cmd (c->port, CCR_DISRX);
	} else if (! cx_receive_enabled(c) && on) {
		outb (CAR(c->port), c->num & 3);
		ier = inb (IER(c->port));
		if (c->mode == M_ASYNC)
			outb (IER(c->port), ier | (IER_RXD | IER_RET));
		else
			outb (IER(c->port), ier | IER_RXD);
 		cx_cmd (c->port, CCR_ENRX);
	}
}