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
struct work_request_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEN__ABORT_REQ_ULP ; 
 int /*<<< orphan*/  LEN__ABORT_RPL_ULP ; 
 int /*<<< orphan*/  LEN__SET_TCB_FIELD_ULP ; 
 int roundup2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
del_hashfilter_wrlen(void)
{

	return (sizeof(struct work_request_hdr) +
	    roundup2(LEN__SET_TCB_FIELD_ULP, 16) +
	    roundup2(LEN__ABORT_REQ_ULP, 16) +
	    roundup2(LEN__ABORT_RPL_ULP, 16));
}