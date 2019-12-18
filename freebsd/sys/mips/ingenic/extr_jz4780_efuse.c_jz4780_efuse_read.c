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
struct jz4780_efuse_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4780_efuse_read_chunk (struct jz4780_efuse_softc*,int,void*,int) ; 

__attribute__((used)) static void
jz4780_efuse_read(struct jz4780_efuse_softc *sc, int addr, void *buf, int len)
{
	int chunk;

	while (len > 0) {
		chunk = (len > 32) ? 32 : len;
		jz4780_efuse_read_chunk(sc, addr, buf, chunk);
		len -= chunk;
		buf = (void *)((uintptr_t)buf + chunk);
		addr += chunk;
	}
}