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
typedef  int u_int32_t ;
struct snd_dbuf {int fmt; int bps; int /*<<< orphan*/  align; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_24BIT ; 
 int AFMT_32BIT ; 
 int /*<<< orphan*/  AFMT_ALIGN (int) ; 
 int AFMT_BPS (int) ; 
 int AFMT_CHANNEL (int) ; 

int
sndbuf_setfmt(struct snd_dbuf *b, u_int32_t fmt)
{
	b->fmt = fmt;
	b->bps = AFMT_BPS(b->fmt);
	b->align = AFMT_ALIGN(b->fmt);
#if 0
	b->bps = AFMT_CHANNEL(b->fmt);
	if (b->fmt & AFMT_16BIT)
		b->bps <<= 1;
	else if (b->fmt & AFMT_24BIT)
		b->bps *= 3;
	else if (b->fmt & AFMT_32BIT)
		b->bps <<= 2;
#endif
	return 0;
}