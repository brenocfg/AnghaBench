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
struct gas_server_handler {struct wpabuf* (* req_cb ) (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;void (* status_cb ) (void*,struct wpabuf*,int) ;int /*<<< orphan*/  list; struct gas_server* gas; void* ctx; int /*<<< orphan*/  adv_proto_id_len; int /*<<< orphan*/  adv_proto_id; } ;
struct gas_server {int /*<<< orphan*/  handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ADV_PROTO_ID_LEN ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct gas_server_handler* os_zalloc (int) ; 

int gas_server_register(struct gas_server *gas,
			const u8 *adv_proto_id, u8 adv_proto_id_len,
			struct wpabuf *
			(*req_cb)(void *ctx, const u8 *sa,
				  const u8 *query, size_t query_len),
			void (*status_cb)(void *ctx, struct wpabuf *resp,
					  int ok),
			void *ctx)
{
	struct gas_server_handler *handler;

	if (!gas || adv_proto_id_len > MAX_ADV_PROTO_ID_LEN)
		return -1;
	handler = os_zalloc(sizeof(*handler));
	if (!handler)
		return -1;

	os_memcpy(handler->adv_proto_id, adv_proto_id, adv_proto_id_len);
	handler->adv_proto_id_len = adv_proto_id_len;
	handler->req_cb = req_cb;
	handler->status_cb = status_cb;
	handler->ctx = ctx;
	handler->gas = gas;
	dl_list_add(&gas->handlers, &handler->list);

	return 0;
}