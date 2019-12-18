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
typedef  int u_int32_t ;
struct twe_softc {int dummy; } ;

/* Variables and functions */
 int TWE_STATUS (struct twe_softc*) ; 
 int TWE_STATUS_ATTENTION_INTERRUPT ; 
 int TWE_STATUS_COMMAND_INTERRUPT ; 
 int TWE_STATUS_HOST_INTERRUPT ; 
 int TWE_STATUS_RESPONSE_INTERRUPT ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  twe_attention_intr (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_check_bits (struct twe_softc*,int) ; 
 int /*<<< orphan*/  twe_command_intr (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_done (struct twe_softc*,int) ; 
 int /*<<< orphan*/  twe_host_intr (struct twe_softc*) ; 

void
twe_intr(struct twe_softc *sc)
{
    u_int32_t		status_reg;

    debug_called(4);

    /*
     * Collect current interrupt status.
     */
    status_reg = TWE_STATUS(sc);
    twe_check_bits(sc, status_reg);

    /*
     * Dispatch based on interrupt status
     */
    if (status_reg & TWE_STATUS_HOST_INTERRUPT)
	twe_host_intr(sc);
    if (status_reg & TWE_STATUS_ATTENTION_INTERRUPT)
	twe_attention_intr(sc);
    if (status_reg & TWE_STATUS_COMMAND_INTERRUPT)
	twe_command_intr(sc);
    if (status_reg & TWE_STATUS_RESPONSE_INTERRUPT)
	twe_done(sc, 1);
}