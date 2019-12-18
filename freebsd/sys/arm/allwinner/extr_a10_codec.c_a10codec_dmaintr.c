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
struct a10codec_chinfo {unsigned int pos; int /*<<< orphan*/  channel; scalar_t__ run; scalar_t__ blocksize; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  a10codec_transfer (struct a10codec_chinfo*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 unsigned int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
a10codec_dmaintr(void *priv)
{
	struct a10codec_chinfo *ch = priv;
	unsigned bufsize;

	bufsize = sndbuf_getsize(ch->buffer);

	ch->pos += ch->blocksize;
	if (ch->pos >= bufsize)
		ch->pos -= bufsize;

	if (ch->run) {
		chn_intr(ch->channel);
		a10codec_transfer(ch);
	}
}