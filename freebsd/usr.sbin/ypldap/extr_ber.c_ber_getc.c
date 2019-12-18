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
typedef  int /*<<< orphan*/  u_char ;
struct ber {int fd; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ber_readbuf (struct ber*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t
ber_getc(struct ber *b, u_char *c)
{
	ssize_t r;
	/*
	 * XXX calling read here is wrong in many ways. The most obvious one
	 * being that we will block till data arrives.
	 * But for now it is _good enough_ *gulp*
	 */
	if (b->fd == -1)
		r = ber_readbuf(b, c, 1);
	else
		r = read(b->fd, c, 1);
	return r;
}