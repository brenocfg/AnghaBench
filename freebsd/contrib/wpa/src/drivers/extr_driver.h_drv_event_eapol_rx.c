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
struct TYPE_2__ {size_t data_len; int /*<<< orphan*/  const* data; int /*<<< orphan*/  const* src; } ;
union wpa_event_data {TYPE_1__ eapol_rx; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_EAPOL_RX ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (void*,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static inline void drv_event_eapol_rx(void *ctx, const u8 *src, const u8 *data,
				      size_t data_len)
{
	union wpa_event_data event;
	os_memset(&event, 0, sizeof(event));
	event.eapol_rx.src = src;
	event.eapol_rx.data = data;
	event.eapol_rx.data_len = data_len;
	wpa_supplicant_event(ctx, EVENT_EAPOL_RX, &event);
}