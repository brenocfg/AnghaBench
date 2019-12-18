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
typedef  int u_int64_t ;
struct snd_dbuf {int prev_total; int blksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDBUF_LOCKASSERT (struct snd_dbuf*) ; 

u_int64_t
sndbuf_getprevblocks(struct snd_dbuf *b)
{
	SNDBUF_LOCKASSERT(b);

	return b->prev_total / b->blksz;
}