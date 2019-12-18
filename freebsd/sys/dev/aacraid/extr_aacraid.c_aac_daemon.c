#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct aac_softc {int /*<<< orphan*/  timeout_id; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  aac_daemontime; } ;
struct aac_fib_header {int dummy; } ;
struct TYPE_2__ {int Size; int XferState; int /*<<< orphan*/  Command; } ;
struct aac_fib {scalar_t__ data; TYPE_1__ Header; } ;
struct aac_command {int /*<<< orphan*/  cm_flags; scalar_t__ cm_datalen; int /*<<< orphan*/  cm_timestamp; struct aac_fib* cm_fib; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_CMD_WAIT ; 
 int AAC_FIBSTATE_ASYNC ; 
 int AAC_FIBSTATE_EMPTY ; 
 int AAC_FIBSTATE_FAST_RESPONSE ; 
 int AAC_FIBSTATE_FROMHOST ; 
 int AAC_FIBSTATE_HOSTOWNED ; 
 int AAC_FIBSTATE_INITIALISED ; 
 int AAC_FIBSTATE_NORM ; 
 int AAC_FIBSTATE_REXPECTED ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SendHostTime ; 
 int /*<<< orphan*/  aacraid_alloc_command (struct aac_softc*,struct aac_command**) ; 
 int /*<<< orphan*/  aacraid_map_command_sg (struct aac_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aacraid_release_command (struct aac_command*) ; 
 scalar_t__ callout_active (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_uptime ; 
 int /*<<< orphan*/  timeout (void (*) (void*),void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

__attribute__((used)) static void
aac_daemon(void *arg)
{
	struct aac_softc *sc;
	struct timeval tv;
	struct aac_command *cm;
	struct aac_fib *fib;

	sc = arg;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

#if __FreeBSD_version >= 800000
	mtx_assert(&sc->aac_io_lock, MA_OWNED);
	if (callout_pending(&sc->aac_daemontime) ||
	    callout_active(&sc->aac_daemontime) == 0)
		return;
#else
	mtx_lock(&sc->aac_io_lock);
#endif
	getmicrotime(&tv);

	if (!aacraid_alloc_command(sc, &cm)) {
		fib = cm->cm_fib;
		cm->cm_timestamp = time_uptime;
		cm->cm_datalen = 0;
		cm->cm_flags |= AAC_CMD_WAIT;

		fib->Header.Size = 
			sizeof(struct aac_fib_header) + sizeof(u_int32_t);
		fib->Header.XferState =
			AAC_FIBSTATE_HOSTOWNED   |
			AAC_FIBSTATE_INITIALISED |
			AAC_FIBSTATE_EMPTY	 |
			AAC_FIBSTATE_FROMHOST	 |
			AAC_FIBSTATE_REXPECTED   |
			AAC_FIBSTATE_NORM	 |
			AAC_FIBSTATE_ASYNC	 |
			AAC_FIBSTATE_FAST_RESPONSE;
		fib->Header.Command = SendHostTime;
		*(uint32_t *)fib->data = tv.tv_sec;

		aacraid_map_command_sg(cm, NULL, 0, 0);
		aacraid_release_command(cm);
	}

#if __FreeBSD_version >= 800000
	callout_schedule(&sc->aac_daemontime, 30 * 60 * hz);
#else
	mtx_unlock(&sc->aac_io_lock);
	tv.tv_sec = 30 * 60;
	tv.tv_usec = 0;
	sc->timeout_id = timeout(aac_daemon, (void *)sc, tvtohz(&tv));
#endif
}