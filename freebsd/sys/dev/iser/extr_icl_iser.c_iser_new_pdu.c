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
struct iser_conn {int dummy; } ;
struct icl_pdu {int /*<<< orphan*/ * ip_bhs; struct icl_conn* ip_conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  iscsi_header; } ;
struct icl_iser_pdu {TYPE_1__ desc; struct icl_pdu icl_pdu; struct iser_conn* iser_conn; } ;
struct icl_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_WARN (char*,int) ; 
 int M_ZERO ; 
 int /*<<< orphan*/  icl_pdu_zone ; 
 struct iser_conn* icl_to_iser_conn (struct icl_conn*) ; 
 struct icl_iser_pdu* uma_zalloc (int /*<<< orphan*/ ,int) ; 

struct icl_pdu *
iser_new_pdu(struct icl_conn *ic, int flags)
{
	struct icl_iser_pdu *iser_pdu;
	struct icl_pdu *ip;
	struct iser_conn *iser_conn = icl_to_iser_conn(ic);

	iser_pdu = uma_zalloc(icl_pdu_zone, flags | M_ZERO);
	if (iser_pdu == NULL) {
		ISER_WARN("failed to allocate %zd bytes", sizeof(*iser_pdu));
		return (NULL);
	}

	iser_pdu->iser_conn = iser_conn;
	ip = &iser_pdu->icl_pdu;
	ip->ip_conn = ic;
	ip->ip_bhs = &iser_pdu->desc.iscsi_header;

	return (ip);
}