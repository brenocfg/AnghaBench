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
struct icl_pdu {int /*<<< orphan*/  ip_conn; } ;

/* Variables and functions */
 struct icl_pdu* icl_pdu_new (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct icl_pdu *
cfiscsi_pdu_new_response(struct icl_pdu *request, int flags)
{

	return (icl_pdu_new(request->ip_conn, flags));
}