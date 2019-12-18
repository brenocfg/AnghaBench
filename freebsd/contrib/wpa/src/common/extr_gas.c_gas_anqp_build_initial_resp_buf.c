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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 struct wpabuf* gas_anqp_build_initial_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_anqp_set_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

struct wpabuf * gas_anqp_build_initial_resp_buf(u8 dialog_token,
						u16 status_code,
						u16 comeback_delay,
						struct wpabuf *payload)
{
	struct wpabuf *buf;

	buf = gas_anqp_build_initial_resp(dialog_token, status_code,
					  comeback_delay,
					  payload ? wpabuf_len(payload) : 0);
	if (buf == NULL)
		return NULL;

	if (payload)
		wpabuf_put_buf(buf, payload);

	gas_anqp_set_len(buf);

	return buf;
}