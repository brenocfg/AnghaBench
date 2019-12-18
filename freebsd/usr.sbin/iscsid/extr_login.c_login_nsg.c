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
struct pdu {scalar_t__ pdu_bhs; } ;
struct iscsi_bhs_login_response {int bhslr_flags; } ;

/* Variables and functions */

__attribute__((used)) static int
login_nsg(const struct pdu *response)
{
	struct iscsi_bhs_login_response *bhslr;

	bhslr = (struct iscsi_bhs_login_response *)response->pdu_bhs;

	return (bhslr->bhslr_flags & 0x03);
}