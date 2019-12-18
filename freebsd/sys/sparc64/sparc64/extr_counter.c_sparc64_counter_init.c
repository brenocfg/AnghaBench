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
struct timecounter {int /*<<< orphan*/  tc_quality; struct ct_softc* tc_priv; int /*<<< orphan*/  tc_name; int /*<<< orphan*/  tc_frequency; int /*<<< orphan*/  tc_counter_mask; int /*<<< orphan*/  tc_get_timecount; } ;
struct ct_softc {scalar_t__ sc_offset; int /*<<< orphan*/  sc_handle; int /*<<< orphan*/  sc_tag; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_FREQ ; 
 int /*<<< orphan*/  COUNTER_MASK ; 
 int /*<<< orphan*/  COUNTER_QUALITY ; 
 scalar_t__ CTR_CT0 ; 
 scalar_t__ CTR_CT1 ; 
 scalar_t__ CTR_LIMIT ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bus_space_write_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_get_timecount ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_init (struct timecounter*) ; 

void
sparc64_counter_init(const char *name, bus_space_tag_t tag,
    bus_space_handle_t handle, bus_addr_t offset)
{
	struct timecounter *tc;
	struct ct_softc *sc;

	printf("initializing counter-timer\n");
	/*
	 * Turn off interrupts from both counters.  Set the limit to the
	 * maximum value (although that should not change anything with
	 * CTLR_INTEN and CTLR_PERIODIC off).
	 */
	bus_space_write_8(tag, handle, offset + CTR_CT0 + CTR_LIMIT,
	    COUNTER_MASK);
	bus_space_write_8(tag, handle, offset + CTR_CT1 + CTR_LIMIT,
	    COUNTER_MASK);
	/* Register as a time counter. */
	tc = malloc(sizeof(*tc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK);
	sc->sc_tag = tag;
	sc->sc_handle = handle;
	sc->sc_offset = offset + CTR_CT0;
	tc->tc_get_timecount = counter_get_timecount;
	tc->tc_counter_mask = COUNTER_MASK;
	tc->tc_frequency = COUNTER_FREQ;
	tc->tc_name = strdup(name, M_DEVBUF);
	tc->tc_priv = sc;
	tc->tc_quality = COUNTER_QUALITY;
	tc_init(tc);
}