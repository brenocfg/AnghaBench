#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iser_conn {int /*<<< orphan*/  login_req_buf; } ;
struct icl_pdu {size_t ip_data_len; TYPE_1__* ip_bhs; } ;
struct icl_conn {int dummy; } ;
struct TYPE_2__ {int bhs_opcode; } ;

/* Variables and functions */
 int ISCSI_BHS_OPCODE_LOGIN_REQUEST ; 
 int ISCSI_BHS_OPCODE_TEXT_REQUEST ; 
 int /*<<< orphan*/  ISER_DBG (char*) ; 
 struct iser_conn* icl_to_iser_conn (struct icl_conn*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

int
iser_conn_pdu_append_data(struct icl_conn *ic, struct icl_pdu *request,
			  const void *addr, size_t len, int flags)
{
	struct iser_conn *iser_conn = icl_to_iser_conn(ic);

	if (request->ip_bhs->bhs_opcode & ISCSI_BHS_OPCODE_LOGIN_REQUEST ||
	    request->ip_bhs->bhs_opcode & ISCSI_BHS_OPCODE_TEXT_REQUEST) {
		ISER_DBG("copy to login buff");
		memcpy(iser_conn->login_req_buf, addr, len);
		request->ip_data_len = len;
	}

	return (0);
}