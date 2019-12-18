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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  tmp ;
struct zyd_softc {int dummy; } ;
struct zyd_pair {int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_CMD_FLAG_READ ; 
 int /*<<< orphan*/  ZYD_CMD_IORD ; 
 int /*<<< orphan*/  ZYD_REG32_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZYD_REG32_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int zyd_cmd (struct zyd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct zyd_pair*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zyd_read32(struct zyd_softc *sc, uint16_t reg, uint32_t *val)
{
	struct zyd_pair tmp[2];
	uint16_t regs[2];
	int error;

	regs[0] = htole16(ZYD_REG32_HI(reg));
	regs[1] = htole16(ZYD_REG32_LO(reg));
	error = zyd_cmd(sc, ZYD_CMD_IORD, regs, sizeof(regs), tmp, sizeof(tmp),
	    ZYD_CMD_FLAG_READ);
	if (error == 0)
		*val = le16toh(tmp[0].val) << 16 | le16toh(tmp[1].val);
	return (error);
}