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
struct p2p_message {int /*<<< orphan*/ * wfd_subelems; int /*<<< orphan*/ * wps_attributes; int /*<<< orphan*/ * p2p_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void p2p_parse_free(struct p2p_message *msg)
{
	wpabuf_free(msg->p2p_attributes);
	msg->p2p_attributes = NULL;
	wpabuf_free(msg->wps_attributes);
	msg->wps_attributes = NULL;
#ifdef CONFIG_WIFI_DISPLAY
	wpabuf_free(msg->wfd_subelems);
	msg->wfd_subelems = NULL;
#endif /* CONFIG_WIFI_DISPLAY */
}