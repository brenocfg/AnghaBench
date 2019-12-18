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
struct icl_pdu {scalar_t__ ip_ahs_len; int /*<<< orphan*/ * ip_ahs_mbuf; int /*<<< orphan*/  ip_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_DEBUG (char*) ; 
 int /*<<< orphan*/ * icl_conn_receive (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ icl_pdu_ahs_length (struct icl_pdu*) ; 

__attribute__((used)) static int
icl_pdu_receive_ahs(struct icl_pdu *request, size_t *availablep)
{

	request->ip_ahs_len = icl_pdu_ahs_length(request);
	if (request->ip_ahs_len == 0)
		return (0);

	request->ip_ahs_mbuf = icl_conn_receive(request->ip_conn,
	    request->ip_ahs_len);
	if (request->ip_ahs_mbuf == NULL) {
		ICL_DEBUG("failed to receive AHS");
		return (-1);
	}

	*availablep -= request->ip_ahs_len;
	return (0);
}