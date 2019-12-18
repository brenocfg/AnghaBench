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
struct wpabuf {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  anqp_add_elem (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_anqp_elem (struct hostapd_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anqp_add_override(struct hostapd_data *hapd, struct wpabuf *buf,
			     u16 infoid)
{
	if (get_anqp_elem(hapd, infoid)) {
		anqp_add_elem(hapd, buf, infoid);
		return 1;
	}

	return 0;
}