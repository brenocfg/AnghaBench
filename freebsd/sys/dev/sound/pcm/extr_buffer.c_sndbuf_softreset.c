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
struct snd_dbuf {scalar_t__ bufsize; scalar_t__ buf; scalar_t__ rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  sndbuf_clear (struct snd_dbuf*,scalar_t__) ; 

void
sndbuf_softreset(struct snd_dbuf *b)
{
	b->rl = 0;
	if (b->buf && b->bufsize > 0)
		sndbuf_clear(b, b->bufsize);
}