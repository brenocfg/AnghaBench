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
struct radius_session {struct radius_server_data* server; } ;
struct radius_server_data {size_t eap_req_id_text_len; char const* eap_req_id_text; } ;

/* Variables and functions */

__attribute__((used)) static const char * radius_server_get_eap_req_id_text(void *ctx, size_t *len)
{
	struct radius_session *sess = ctx;
	struct radius_server_data *data = sess->server;
	*len = data->eap_req_id_text_len;
	return data->eap_req_id_text;
}