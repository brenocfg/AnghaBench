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
struct snd_dbuf {scalar_t__ bufsize; scalar_t__ rl; scalar_t__ rp; int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sndbuf_getbuf (struct snd_dbuf*) ; 
 int /*<<< orphan*/  sndbuf_zerodata (int /*<<< orphan*/ ) ; 

void
sndbuf_fillsilence(struct snd_dbuf *b)
{
	if (b->bufsize > 0)
		memset(sndbuf_getbuf(b), sndbuf_zerodata(b->fmt), b->bufsize);
	b->rp = 0;
	b->rl = b->bufsize;
}