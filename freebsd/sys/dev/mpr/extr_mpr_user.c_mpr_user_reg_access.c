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
struct mpr_softc {int dummy; } ;
struct TYPE_3__ {int Command; int /*<<< orphan*/  RegData; int /*<<< orphan*/  RegOffset; } ;
typedef  TYPE_1__ mpr_reg_access_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPR_USER ; 
#define  REG_IO_READ 131 
#define  REG_IO_WRITE 130 
#define  REG_MEM_READ 129 
#define  REG_MEM_WRITE 128 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpr_regread (struct mpr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_regwrite (struct mpr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpr_user_reg_access(struct mpr_softc *sc, mpr_reg_access_t *data)
{
	int	status = 0;

	switch (data->Command) {
		/*
		 * IO access is not supported.
		 */
		case REG_IO_READ:
		case REG_IO_WRITE:
			mpr_dprint(sc, MPR_USER, "IO access is not supported. "
			    "Use memory access.");
			status = EINVAL;
			break;

		case REG_MEM_READ:
			data->RegData = mpr_regread(sc, data->RegOffset);
			break;

		case REG_MEM_WRITE:
			mpr_regwrite(sc, data->RegOffset, data->RegData);
			break;

		default:
			status = EINVAL;
			break;
	}

	return (status);
}