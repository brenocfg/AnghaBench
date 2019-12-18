#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int dummy; } ;
struct sockopt_data {int valsize; } ;
struct ip_fw_chain {int dummy; } ;
struct _ipfw_obj_header {int dummy; } ;
struct TYPE_3__ {scalar_t__ opcode; } ;
typedef  TYPE_1__ ip_fw3_opheader ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ IP_FW_TABLE_XDESTROY ; 
 scalar_t__ IP_FW_TABLE_XFLUSH ; 
 int destroy_table (struct ip_fw_chain*,struct tid_info*) ; 
 int flush_table (struct ip_fw_chain*,struct tid_info*) ; 
 int /*<<< orphan*/  objheader_to_ti (struct _ipfw_obj_header*,struct tid_info*) ; 

__attribute__((used)) static int
flush_table_v0(struct ip_fw_chain *ch, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	int error;
	struct _ipfw_obj_header *oh;
	struct tid_info ti;

	if (sd->valsize != sizeof(*oh))
		return (EINVAL);

	oh = (struct _ipfw_obj_header *)op3;
	objheader_to_ti(oh, &ti);

	if (op3->opcode == IP_FW_TABLE_XDESTROY)
		error = destroy_table(ch, &ti);
	else if (op3->opcode == IP_FW_TABLE_XFLUSH)
		error = flush_table(ch, &ti);
	else
		return (ENOTSUP);

	return (error);
}