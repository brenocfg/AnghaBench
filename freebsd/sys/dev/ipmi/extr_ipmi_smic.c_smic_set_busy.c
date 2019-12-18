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
struct ipmi_softc {int dummy; } ;

/* Variables and functions */
 int INB (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct ipmi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SMIC_FLAGS ; 
 int SMIC_STATUS_BUSY ; 
 int SMIC_STATUS_RESERVED ; 

__attribute__((used)) static void
smic_set_busy(struct ipmi_softc *sc)
{
	int flags;

	flags = INB(sc, SMIC_FLAGS);
	flags |= SMIC_STATUS_BUSY;
	flags &= ~SMIC_STATUS_RESERVED;
	OUTB(sc, SMIC_FLAGS, flags);
}