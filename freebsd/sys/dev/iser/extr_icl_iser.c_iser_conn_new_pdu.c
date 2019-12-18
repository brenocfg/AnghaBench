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
struct icl_conn {int dummy; } ;

/* Variables and functions */
 struct icl_pdu* iser_new_pdu (struct icl_conn*,int) ; 

struct icl_pdu *
iser_conn_new_pdu(struct icl_conn *ic, int flags)
{
	return (iser_new_pdu(ic, flags));
}