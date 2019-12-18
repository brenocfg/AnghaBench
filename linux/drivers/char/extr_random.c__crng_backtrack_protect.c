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
struct crng_state {int /*<<< orphan*/  lock; int /*<<< orphan*/ * state; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ CHACHA_BLOCK_SIZE ; 
 scalar_t__ CHACHA_KEY_SIZE ; 
 int /*<<< orphan*/  extract_crng (int /*<<< orphan*/ *) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _crng_backtrack_protect(struct crng_state *crng,
				    __u8 tmp[CHACHA_BLOCK_SIZE], int used)
{
	unsigned long	flags;
	__u32		*s, *d;
	int		i;

	used = round_up(used, sizeof(__u32));
	if (used + CHACHA_KEY_SIZE > CHACHA_BLOCK_SIZE) {
		extract_crng(tmp);
		used = 0;
	}
	spin_lock_irqsave(&crng->lock, flags);
	s = (__u32 *) &tmp[used];
	d = &crng->state[4];
	for (i=0; i < 8; i++)
		*d++ ^= *s++;
	spin_unlock_irqrestore(&crng->lock, flags);
}