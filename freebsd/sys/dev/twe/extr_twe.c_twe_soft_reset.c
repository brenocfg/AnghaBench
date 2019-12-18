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
typedef  int /*<<< orphan*/  u_int32_t ;
struct twe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_AEN_SOFT_RESET ; 
 int /*<<< orphan*/  TWE_CONTROL (struct twe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWE_CONTROL_CLEAR_ATTENTION_INTERRUPT ; 
 int /*<<< orphan*/  TWE_IO_ASSERT_LOCKED (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_SOFT_RESET (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_STATUS (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_STATUS_ATTENTION_INTERRUPT ; 
 scalar_t__ TWE_STATUS_ERRORS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ twe_check_bits (struct twe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ twe_drain_aen_queue (struct twe_softc*) ; 
 scalar_t__ twe_drain_response_queue (struct twe_softc*) ; 
 scalar_t__ twe_find_aen (struct twe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*) ; 
 scalar_t__ twe_wait_status (struct twe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
twe_soft_reset(struct twe_softc *sc)
{
    u_int32_t		status_reg;

    debug_called(2);

    TWE_IO_ASSERT_LOCKED(sc);
    TWE_SOFT_RESET(sc);

    if (twe_wait_status(sc, TWE_STATUS_ATTENTION_INTERRUPT, 30)) {
	twe_printf(sc, "no attention interrupt\n");
	return(1);
    }
    TWE_CONTROL(sc, TWE_CONTROL_CLEAR_ATTENTION_INTERRUPT);
    if (twe_drain_aen_queue(sc)) {
	twe_printf(sc, "can't drain AEN queue\n");
	return(1);
    }
    if (twe_find_aen(sc, TWE_AEN_SOFT_RESET)) {
	twe_printf(sc, "reset not reported\n");
	return(1);
    }
    status_reg = TWE_STATUS(sc);
    if (TWE_STATUS_ERRORS(status_reg) || twe_check_bits(sc, status_reg)) {
	twe_printf(sc, "controller errors detected\n");
	return(1);
    }
    if (twe_drain_response_queue(sc)) {
	twe_printf(sc, "can't drain response queue\n");
	return(1);
    }
    return(0);
}