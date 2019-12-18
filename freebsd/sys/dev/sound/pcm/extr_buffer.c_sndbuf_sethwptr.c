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
struct snd_dbuf {unsigned int hp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDBUF_LOCKASSERT (struct snd_dbuf*) ; 

void
sndbuf_sethwptr(struct snd_dbuf *b, unsigned int ptr)
{
	SNDBUF_LOCKASSERT(b);

	b->hp = ptr;
}