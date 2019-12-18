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
typedef  int /*<<< orphan*/  u_char ;
struct ipmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCS_CONTROL_WRITE_END ; 
 int /*<<< orphan*/  KCS_CTL_STS ; 
 int /*<<< orphan*/  KCS_DATA ; 
 int KCS_STATUS_IBF ; 
 scalar_t__ KCS_STATUS_STATE (int) ; 
 scalar_t__ KCS_STATUS_STATE_WRITE ; 
 int /*<<< orphan*/  OUTB (struct ipmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcs_clear_obf (struct ipmi_softc*,int) ; 
 int kcs_wait_for_ibf (struct ipmi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kcs_write_last_byte(struct ipmi_softc *sc, u_char data)
{
	int status;

	/* Write end to command */
	OUTB(sc, KCS_CTL_STS, KCS_CONTROL_WRITE_END);

	/* Wait for IBF = 0 */
	status = kcs_wait_for_ibf(sc, 0);
	if (status & KCS_STATUS_IBF)
		return (0);

	if (KCS_STATUS_STATE(status) != KCS_STATUS_STATE_WRITE)
		/* error state */
		return (0);

	/* Clear OBF */
	kcs_clear_obf(sc, status);

	/* Send data byte to DATA. */
	OUTB(sc, KCS_DATA, data);
	return (1);
}