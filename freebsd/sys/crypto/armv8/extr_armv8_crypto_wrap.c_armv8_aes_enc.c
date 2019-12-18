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
typedef  int /*<<< orphan*/  uint8x16_t ;

/* Variables and functions */
 int /*<<< orphan*/  vaeseq_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  vaesmcq_u8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veorq_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static uint8x16_t
armv8_aes_enc(int rounds, const uint8x16_t *keysched, const uint8x16_t from)
{
	uint8x16_t tmp;
	int i;

	tmp = from;
	for (i = 0; i < rounds - 1; i += 2) {
		tmp = vaeseq_u8(tmp, keysched[i]);
		tmp = vaesmcq_u8(tmp);
		tmp = vaeseq_u8(tmp, keysched[i + 1]);
		tmp = vaesmcq_u8(tmp);
	}

	tmp = vaeseq_u8(tmp, keysched[rounds - 1]);
	tmp = vaesmcq_u8(tmp);
	tmp = vaeseq_u8(tmp, keysched[rounds]);
	tmp = veorq_u8(tmp, keysched[rounds + 1]);

	return (tmp);
}