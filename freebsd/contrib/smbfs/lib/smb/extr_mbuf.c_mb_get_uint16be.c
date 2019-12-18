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
typedef  int /*<<< orphan*/  u_int16_t ;
struct mbdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int mb_get_uint16 (struct mbdata*,int /*<<< orphan*/ *) ; 

int
mb_get_uint16be(struct mbdata *mbp, u_int16_t *x) {
	u_int16_t v;
	int error = mb_get_uint16(mbp, &v);

	*x = be16toh(v);
	return error;
}