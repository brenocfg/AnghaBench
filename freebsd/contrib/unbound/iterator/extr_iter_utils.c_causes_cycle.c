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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint16_t ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * local_alias; void* qclass; void* qtype; int /*<<< orphan*/ * qname; } ;
struct module_qstate {int /*<<< orphan*/  is_valrec; int /*<<< orphan*/  is_priming; TYPE_1__* env; } ;
struct TYPE_2__ {int (* detect_cycle ) (struct module_qstate*,struct query_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BIT_CD ; 
 int BIT_RD ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_detect_cycle (int (*) (struct module_qstate*,struct query_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int stub1 (struct module_qstate*,struct query_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
causes_cycle(struct module_qstate* qstate, uint8_t* name, size_t namelen,
	uint16_t t, uint16_t c)
{
	struct query_info qinf;
	qinf.qname = name;
	qinf.qname_len = namelen;
	qinf.qtype = t;
	qinf.qclass = c;
	qinf.local_alias = NULL;
	fptr_ok(fptr_whitelist_modenv_detect_cycle(
		qstate->env->detect_cycle));
	return (*qstate->env->detect_cycle)(qstate, &qinf, 
		(uint16_t)(BIT_RD|BIT_CD), qstate->is_priming,
		qstate->is_valrec);
}