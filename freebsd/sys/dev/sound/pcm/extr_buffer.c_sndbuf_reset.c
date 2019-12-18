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
struct snd_dbuf {scalar_t__ bufsize; scalar_t__ buf; scalar_t__ xrun; scalar_t__ total; scalar_t__ prev_total; scalar_t__ dl; scalar_t__ rl; scalar_t__ rp; scalar_t__ hp; } ;

/* Variables and functions */
 int /*<<< orphan*/  sndbuf_clear (struct snd_dbuf*,scalar_t__) ; 
 int /*<<< orphan*/  sndbuf_clearshadow (struct snd_dbuf*) ; 

void
sndbuf_reset(struct snd_dbuf *b)
{
	b->hp = 0;
	b->rp = 0;
	b->rl = 0;
	b->dl = 0;
	b->prev_total = 0;
	b->total = 0;
	b->xrun = 0;
	if (b->buf && b->bufsize > 0)
		sndbuf_clear(b, b->bufsize);
	sndbuf_clearshadow(b);
}