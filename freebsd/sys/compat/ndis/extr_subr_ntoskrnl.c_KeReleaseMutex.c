#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int dh_sigstate; } ;
struct TYPE_4__ {TYPE_2__ km_header; int /*<<< orphan*/ * km_ownerthread; int /*<<< orphan*/  km_abandoned; } ;
typedef  TYPE_1__ kmutant ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int STATUS_MUTANT_NOT_OWNED ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntoskrnl_dispatchlock ; 
 int /*<<< orphan*/  ntoskrnl_waittest (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
KeReleaseMutex(kmutant *kmutex, uint8_t kwait)
{
	uint32_t		prevstate;

	mtx_lock(&ntoskrnl_dispatchlock);
	prevstate = kmutex->km_header.dh_sigstate;
	if (kmutex->km_ownerthread != curthread) {
		mtx_unlock(&ntoskrnl_dispatchlock);
		return (STATUS_MUTANT_NOT_OWNED);
	}

	kmutex->km_header.dh_sigstate++;
	kmutex->km_abandoned = FALSE;

	if (kmutex->km_header.dh_sigstate == 1) {
		kmutex->km_ownerthread = NULL;
		ntoskrnl_waittest(&kmutex->km_header, IO_NO_INCREMENT);
	}

	mtx_unlock(&ntoskrnl_dispatchlock);

	return (prevstate);
}