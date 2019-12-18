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
typedef  int /*<<< orphan*/  uint16_t ;
struct zyd_softc {int dummy; } ;
struct zyd_pair {void* val; void* reg; } ;
typedef  int /*<<< orphan*/  pair ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_CMD_IOWR ; 
 void* htole16 (int /*<<< orphan*/ ) ; 
 int zyd_cmd (struct zyd_softc*,int /*<<< orphan*/ ,struct zyd_pair*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zyd_write16(struct zyd_softc *sc, uint16_t reg, uint16_t val)
{
	struct zyd_pair pair;

	pair.reg = htole16(reg);
	pair.val = htole16(val);

	return zyd_cmd(sc, ZYD_CMD_IOWR, &pair, sizeof(pair), NULL, 0, 0);
}