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
struct hostapd_radius_attr {int /*<<< orphan*/  val; struct hostapd_radius_attr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct hostapd_radius_attr*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void hostapd_config_free_radius_attr(struct hostapd_radius_attr *attr)
{
	struct hostapd_radius_attr *prev;

	while (attr) {
		prev = attr;
		attr = attr->next;
		wpabuf_free(prev->val);
		os_free(prev);
	}
}