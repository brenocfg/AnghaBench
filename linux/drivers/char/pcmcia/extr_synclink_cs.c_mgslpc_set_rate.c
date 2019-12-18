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
typedef  int /*<<< orphan*/  MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ BGR ; 
 scalar_t__ CCR2 ; 
 int read_reg (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 

__attribute__((used)) static void mgslpc_set_rate(MGSLPC_INFO *info, unsigned char channel, unsigned int rate)
{
	unsigned int M, N;
	unsigned char val;

	/* note:standard BRG mode is broken in V3.2 chip
	 * so enhanced mode is always used
	 */

	if (rate) {
		N = 3686400 / rate;
		if (!N)
			N = 1;
		N >>= 1;
		for (M = 1; N > 64 && M < 16; M++)
			N >>= 1;
		N--;

		/* BGR[5..0] = N
		 * BGR[9..6] = M
		 * BGR[7..0] contained in BGR register
		 * BGR[9..8] contained in CCR2[7..6]
		 * divisor = (N+1)*2^M
		 *
		 * Note: M *must* not be zero (causes asymetric duty cycle)
		 */
		write_reg(info, (unsigned char) (channel + BGR),
				  (unsigned char) ((M << 6) + N));
		val = read_reg(info, (unsigned char) (channel + CCR2)) & 0x3f;
		val |= ((M << 4) & 0xc0);
		write_reg(info, (unsigned char) (channel + CCR2), val);
	}
}