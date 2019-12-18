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
typedef  int /*<<< orphan*/  tmp ;
struct zyd_softc {int dummy; } ;
struct zyd_pair {int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_CMD_FLAG_READ ; 
 int /*<<< orphan*/  ZYD_CMD_IORD ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int zyd_cmd (struct zyd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct zyd_pair*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zyd_read16(struct zyd_softc *sc, uint16_t reg, uint16_t *val)
{
	struct zyd_pair tmp;
	int error;

	reg = htole16(reg);
	error = zyd_cmd(sc, ZYD_CMD_IORD, &reg, sizeof(reg), &tmp, sizeof(tmp),
	    ZYD_CMD_FLAG_READ);
	if (error == 0)
		*val = le16toh(tmp.val);
	return (error);
}