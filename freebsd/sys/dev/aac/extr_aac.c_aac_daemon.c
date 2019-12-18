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
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct aac_softc {int /*<<< orphan*/  aac_daemontime; int /*<<< orphan*/  aac_io_lock; } ;
struct aac_fib {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SendHostTime ; 
 int /*<<< orphan*/  aac_alloc_sync_fib (struct aac_softc*,struct aac_fib**) ; 
 int /*<<< orphan*/  aac_release_sync_fib (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_sync_fib (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_fib*,int) ; 
 scalar_t__ callout_active (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aac_daemon(void *arg)
{
	struct timeval tv;
	struct aac_softc *sc;
	struct aac_fib *fib;

	sc = arg;
	mtx_assert(&sc->aac_io_lock, MA_OWNED);

	if (callout_pending(&sc->aac_daemontime) ||
	    callout_active(&sc->aac_daemontime) == 0)
		return;
	getmicrotime(&tv);
	aac_alloc_sync_fib(sc, &fib);
	*(uint32_t *)fib->data = tv.tv_sec;
	aac_sync_fib(sc, SendHostTime, 0, fib, sizeof(uint32_t));
	aac_release_sync_fib(sc);
	callout_schedule(&sc->aac_daemontime, 30 * 60 * hz);
}