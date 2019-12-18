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
struct eapol_callbacks {int dummy; } ;
struct eap_proxy_sm {int dummy; } ;

/* Variables and functions */

struct eap_proxy_sm *
eap_proxy_init(void *eapol_ctx, const struct eapol_callbacks *eapol_cb,
	       void *msg_ctx)
{
	return NULL;
}