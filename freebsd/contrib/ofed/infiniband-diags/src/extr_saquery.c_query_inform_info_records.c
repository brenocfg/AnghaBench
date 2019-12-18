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
struct sa_handle {int dummy; } ;
struct query_params {int dummy; } ;
struct query_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  ir ;
typedef  int /*<<< orphan*/  ib_net64_t ;
typedef  int /*<<< orphan*/  ib_inform_info_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_IIR_COMPMASK_SUBSCRIBERGID ; 
 int /*<<< orphan*/  IB_SA_ATTR_INFORMINFORECORD ; 
 int /*<<< orphan*/  dump_inform_info_record ; 
 int get_and_dump_any_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct query_params*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int parse_iir_subscriber_gid (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_inform_info_records(const struct query_cmd *q,
				    struct sa_handle * h, struct query_params *p,
				    int argc, char *argv[])
{
       int rc = 0;
       ib_inform_info_record_t ir;
       ib_net64_t comp_mask = 0;
       memset(&ir, 0, sizeof(ir));

       if (argc > 0) {
           comp_mask = IB_IIR_COMPMASK_SUBSCRIBERGID;
           if((rc = parse_iir_subscriber_gid(argv[0], &ir)) < 1)
                 return rc;
       }

       return get_and_dump_any_records(h, IB_SA_ATTR_INFORMINFORECORD, 0, comp_mask,
				       &ir, sizeof(ir), dump_inform_info_record, p);

}