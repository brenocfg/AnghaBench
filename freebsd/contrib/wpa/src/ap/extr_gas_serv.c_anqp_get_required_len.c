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
typedef  int /*<<< orphan*/  u16 ;
struct hostapd_data {int dummy; } ;
struct anqp_element {int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 struct anqp_element* get_anqp_elem (struct hostapd_data*,int /*<<< orphan*/  const) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t anqp_get_required_len(struct hostapd_data *hapd,
				    const u16 *infoid,
				    unsigned int num_infoid)
{
	size_t len = 0;
	unsigned int i;

	for (i = 0; i < num_infoid; i++) {
		struct anqp_element *elem = get_anqp_elem(hapd, infoid[i]);

		if (elem)
			len += 2 + 2 + wpabuf_len(elem->payload);
	}

	return len;
}