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
struct snd_dbuf {unsigned int maxsize; unsigned int bufsize; void* buf; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDBUF_F_MANAGED ; 
 int sndbuf_resize (struct snd_dbuf*,int,int) ; 

int
sndbuf_setup(struct snd_dbuf *b, void *buf, unsigned int size)
{
	b->flags &= ~SNDBUF_F_MANAGED;
	if (buf)
		b->flags |= SNDBUF_F_MANAGED;
	b->buf = buf;
	b->maxsize = size;
	b->bufsize = b->maxsize;
	return sndbuf_resize(b, 2, b->maxsize / 2);
}