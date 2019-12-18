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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gas_add_adv_proto_anqp (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* gas_build_initial_req (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int) ; 

struct wpabuf * gas_anqp_build_initial_req(u8 dialog_token, size_t size)
{
	struct wpabuf *buf;

	buf = gas_build_initial_req(dialog_token, 4 + size);
	if (buf == NULL)
		return NULL;

	gas_add_adv_proto_anqp(buf, 0, 0);

	wpabuf_put(buf, 2); /* Query Request Length to be filled */

	return buf;
}