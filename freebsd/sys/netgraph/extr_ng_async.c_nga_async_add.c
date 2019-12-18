#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_char ;
typedef  TYPE_1__* sc_p ;
struct TYPE_3__ {int* abuf; } ;

/* Variables and functions */
 int PPP_ESCAPE ; 
 int /*<<< orphan*/  PPP_FCS (int /*<<< orphan*/ ,int) ; 
 int PPP_FLAG ; 
 int PPP_TRANS ; 

__attribute__((used)) static __inline void
nga_async_add(const sc_p sc, u_int16_t *fcs, u_int32_t accm, int *len, u_char x)
{
	*fcs = PPP_FCS(*fcs, x);
	if ((x < 32 && ((1 << x) & accm))
	    || (x == PPP_ESCAPE)
	    || (x == PPP_FLAG)) {
		sc->abuf[(*len)++] = PPP_ESCAPE;
		x ^= PPP_TRANS;
	}
	sc->abuf[(*len)++] = x;
}