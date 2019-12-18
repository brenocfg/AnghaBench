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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAX_TRNG_RETRIES ; 
 int /*<<< orphan*/  TRNG_OUT_OFFSET ; 
 scalar_t__ ccp_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ccp_softc ; 

u_int
random_ccp_read(void *v, u_int c)
{
	uint32_t *buf;
	u_int i, j;

	KASSERT(c % sizeof(*buf) == 0, ("%u not multiple of u_long", c));

	buf = v;
	for (i = c; i > 0; i -= sizeof(*buf)) {
		for (j = 0; j < MAX_TRNG_RETRIES; j++) {
			*buf = ccp_read_4(g_ccp_softc, TRNG_OUT_OFFSET);
			if (*buf != 0)
				break;
		}
		if (j == MAX_TRNG_RETRIES)
			return (0);
		buf++;
	}
	return (c);

}