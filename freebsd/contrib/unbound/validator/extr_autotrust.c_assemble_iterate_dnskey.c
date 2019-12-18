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
typedef  int /*<<< orphan*/  uint8_t ;
struct autr_ta {size_t rr_len; size_t dname_len; scalar_t__ s; struct autr_ta* next; int /*<<< orphan*/ * rr; } ;

/* Variables and functions */
 scalar_t__ AUTR_STATE_MISSING ; 
 scalar_t__ AUTR_STATE_VALID ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 scalar_t__ sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int
assemble_iterate_dnskey(struct autr_ta** list, uint8_t** rr, size_t* rr_len,
	size_t* dname_len)
{
	while(*list) {
		if(sldns_wirerr_get_type((*list)->rr, (*list)->rr_len,
		   (*list)->dname_len) != LDNS_RR_TYPE_DS &&
			((*list)->s == AUTR_STATE_VALID || 
			 (*list)->s == AUTR_STATE_MISSING)) {
			*rr = (*list)->rr;
			*rr_len = (*list)->rr_len;
			*dname_len = (*list)->dname_len;
			*list = (*list)->next;
			return 1;
		}
		*list = (*list)->next;
	}
	return 0;
}