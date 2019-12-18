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
 int /*<<< orphan*/  KCS_STATUS_IBF ; 
 int kcs_wait (struct ipmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kcs_wait_for_ibf(struct ipmi_softc *sc, bool level)
{

	return (kcs_wait(sc, level ? KCS_STATUS_IBF : 0, KCS_STATUS_IBF));
}