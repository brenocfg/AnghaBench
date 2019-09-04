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
struct active_request_slot {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void xmulti_remove_handle(struct active_request_slot *slot)
{
#ifdef USE_CURL_MULTI
	curl_multi_remove_handle(curlm, slot->curl);
#endif
}