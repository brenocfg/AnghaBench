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
typedef  int uint32_t ;
struct hn_softc {int /*<<< orphan*/  hn_rndis_rid; } ;

/* Variables and functions */
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline uint32_t
hn_rndis_rid(struct hn_softc *sc)
{
	uint32_t rid;

again:
	rid = atomic_fetchadd_int(&sc->hn_rndis_rid, 1);
	if (rid == 0)
		goto again;

	/* Use upper 16 bits for non-compat RNDIS messages. */
	return ((rid & 0xffff) << 16);
}