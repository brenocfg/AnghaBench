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
struct jzsmb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBENB ; 
 int /*<<< orphan*/  SMBENBST ; 
 int SMBENBST_SMBEN ; 
 int /*<<< orphan*/  SMBENB_SMBENB ; 
 int /*<<< orphan*/  SMB_ASSERT_LOCKED (struct jzsmb_softc*) ; 
 int SMB_READ (struct jzsmb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMB_WRITE (struct jzsmb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jzsmb_enable(struct jzsmb_softc *sc, int enable)
{
	SMB_ASSERT_LOCKED(sc);

	if (enable) {
		SMB_WRITE(sc, SMBENB, SMBENB_SMBENB);
		while ((SMB_READ(sc, SMBENBST) & SMBENBST_SMBEN) == 0)
			;
	} else {
		SMB_WRITE(sc, SMBENB, 0);
		while ((SMB_READ(sc, SMBENBST) & SMBENBST_SMBEN) != 0)
			;
	}

	return (0);
}