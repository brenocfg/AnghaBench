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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ifx_deu_des (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t,int,int) ; 

void ifx_deu_des_cbc (void *ctx, uint8_t *dst, const uint8_t *src,
                uint8_t *iv, size_t nbytes, int encdec, int inplace)
{
     ifx_deu_des (ctx, dst, src, iv, nbytes, encdec, 1);
}