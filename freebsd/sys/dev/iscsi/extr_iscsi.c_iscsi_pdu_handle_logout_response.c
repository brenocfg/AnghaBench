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
struct icl_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 

__attribute__((used)) static void
iscsi_pdu_handle_logout_response(struct icl_pdu *response)
{

	ISCSI_SESSION_DEBUG(PDU_SESSION(response), "logout response");
	icl_pdu_free(response);
}