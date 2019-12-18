#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  keep_tcal_on_ovf; } ;
struct TYPE_4__ {int /*<<< orphan*/  keep_tcal_on_ovf; } ;
struct TYPE_6__ {TYPE_2__ insn; TYPE_1__ query; } ;
struct pt_conf_flags {TYPE_3__ variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_conf_flags*,int /*<<< orphan*/ ,int) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_insn_init_qry_flags(struct pt_conf_flags *qflags,
				  const struct pt_conf_flags *flags)
{
	if (!qflags || !flags)
		return -pte_internal;

	memset(qflags, 0, sizeof(*qflags));
	qflags->variant.query.keep_tcal_on_ovf =
		flags->variant.insn.keep_tcal_on_ovf;

	return 0;
}