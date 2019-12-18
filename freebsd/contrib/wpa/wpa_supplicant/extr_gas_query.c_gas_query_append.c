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
typedef  int /*<<< orphan*/  u8 ;
struct gas_query_pending {int /*<<< orphan*/  resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int gas_query_append(struct gas_query_pending *query, const u8 *data,
			    size_t len)
{
	if (wpabuf_resize(&query->resp, len) < 0) {
		wpa_printf(MSG_DEBUG, "GAS: No memory to store the response");
		return -1;
	}
	wpabuf_put_data(query->resp, data, len);
	return 0;
}