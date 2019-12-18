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
 int /*<<< orphan*/  KCS_DATA ; 
 int KCS_STATUS_OBF ; 

__attribute__((used)) static void
kcs_clear_obf(struct ipmi_softc *sc, int status)
{
	int data;

	/* Clear OBF */
	if (status & KCS_STATUS_OBF) {
		data = INB(sc, KCS_DATA);
	}
}