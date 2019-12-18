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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int dh_size; int /*<<< orphan*/  dh_type; int /*<<< orphan*/  dh_sigstate; int /*<<< orphan*/  dh_waitlisthead; } ;
struct TYPE_5__ {TYPE_1__ k_header; } ;
typedef  TYPE_2__ nt_kevent ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_TYPE_NOTIFICATION_EVENT ; 
 int /*<<< orphan*/  DISP_TYPE_SYNCHRONIZATION_EVENT ; 
 scalar_t__ EVENT_TYPE_NOTIFY ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 

void
KeInitializeEvent(nt_kevent *kevent, uint32_t type, uint8_t state)
{
	InitializeListHead((&kevent->k_header.dh_waitlisthead));
	kevent->k_header.dh_sigstate = state;
	if (type == EVENT_TYPE_NOTIFY)
		kevent->k_header.dh_type = DISP_TYPE_NOTIFICATION_EVENT;
	else
		kevent->k_header.dh_type = DISP_TYPE_SYNCHRONIZATION_EVENT;
	kevent->k_header.dh_size = sizeof(nt_kevent) / sizeof(uint32_t);
}