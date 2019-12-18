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
typedef  int /*<<< orphan*/  u_int8_t ;
struct mbdata {int dummy; } ;

/* Variables and functions */
 int mb_get_mem (struct mbdata*,int /*<<< orphan*/ *,int) ; 

int
mb_get_uint8(struct mbdata *mbp, u_int8_t *x)
{
	return mb_get_mem(mbp, x, 1);
}