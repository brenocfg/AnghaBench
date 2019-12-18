#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 unsigned int CHACHA_KEY_SIZE ; 
 scalar_t__ crng_init ; 
 TYPE_1__ primary_crng ; 
 int /*<<< orphan*/  spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int crng_slow_load(const char *cp, size_t len)
{
	unsigned long		flags;
	static unsigned char	lfsr = 1;
	unsigned char		tmp;
	unsigned		i, max = CHACHA_KEY_SIZE;
	const char *		src_buf = cp;
	char *			dest_buf = (char *) &primary_crng.state[4];

	if (!spin_trylock_irqsave(&primary_crng.lock, flags))
		return 0;
	if (crng_init != 0) {
		spin_unlock_irqrestore(&primary_crng.lock, flags);
		return 0;
	}
	if (len > max)
		max = len;

	for (i = 0; i < max ; i++) {
		tmp = lfsr;
		lfsr >>= 1;
		if (tmp & 1)
			lfsr ^= 0xE1;
		tmp = dest_buf[i % CHACHA_KEY_SIZE];
		dest_buf[i % CHACHA_KEY_SIZE] ^= src_buf[i % len] ^ lfsr;
		lfsr += (tmp << 3) | (tmp >> 5);
	}
	spin_unlock_irqrestore(&primary_crng.lock, flags);
	return 1;
}