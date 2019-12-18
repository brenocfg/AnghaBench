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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  blf_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  Blowfish_decipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
blf_dec(blf_ctx *c, u_int32_t *data, u_int16_t blocks)
{
	u_int32_t *d;
	u_int16_t i;

	d = data;
	for (i = 0; i < blocks; i++) {
		Blowfish_decipher(c, d, d + 1);
		d += 2;
	}
}