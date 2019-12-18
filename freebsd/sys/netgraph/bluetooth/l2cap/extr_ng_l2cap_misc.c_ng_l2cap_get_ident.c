#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  TYPE_1__* ng_l2cap_con_p ;
struct TYPE_4__ {scalar_t__ ident; } ;

/* Variables and functions */
 scalar_t__ NG_L2CAP_FIRST_IDENT ; 
 scalar_t__ NG_L2CAP_NULL_IDENT ; 
 int /*<<< orphan*/ * ng_l2cap_cmd_by_ident (TYPE_1__*,scalar_t__) ; 

u_int8_t
ng_l2cap_get_ident(ng_l2cap_con_p con)
{
	u_int8_t	ident = con->ident + 1;

	if (ident < NG_L2CAP_FIRST_IDENT)
		ident = NG_L2CAP_FIRST_IDENT;

	while (ident != con->ident) {
		if (ng_l2cap_cmd_by_ident(con, ident) == NULL) {
			con->ident = ident;

			return (ident);
		}

		ident ++;
		if (ident < NG_L2CAP_FIRST_IDENT)
			ident = NG_L2CAP_FIRST_IDENT;
	}

	return (NG_L2CAP_NULL_IDENT);
}