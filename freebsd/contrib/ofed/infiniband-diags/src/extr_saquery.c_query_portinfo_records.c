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
struct sa_handle {int dummy; } ;
struct query_params {int dummy; } ;
struct query_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  pir ;
struct TYPE_4__ {int /*<<< orphan*/  options; int /*<<< orphan*/  port_num; int /*<<< orphan*/  lid; } ;
typedef  TYPE_1__ ib_portinfo_record_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_SET_VAL (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_SA_ATTR_PORTINFORECORD ; 
 int /*<<< orphan*/  LID ; 
 int /*<<< orphan*/  OPTIONS ; 
 int /*<<< orphan*/  PIR ; 
 int /*<<< orphan*/  PORTNUM ; 
 int /*<<< orphan*/  dump_one_portinfo_record ; 
 int get_and_dump_any_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,struct query_params*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_lid_and_ports (struct sa_handle*,char*,int*,int*,int*) ; 

__attribute__((used)) static int query_portinfo_records(const struct query_cmd *q,
				  struct sa_handle * h, struct query_params *p,
				  int argc, char *argv[])
{
	ib_portinfo_record_t pir;
	ib_net64_t comp_mask = 0;
	int lid = 0, port = -1, options = -1;

	if (argc > 0)
		parse_lid_and_ports(h, argv[0], &lid, &port, &options);

	memset(&pir, 0, sizeof(pir));
	CHECK_AND_SET_VAL(lid, 16, 0, pir.lid, PIR, LID);
	CHECK_AND_SET_VAL(port, 8, -1, pir.port_num, PIR, PORTNUM);
	CHECK_AND_SET_VAL(options, 8, -1, pir.options, PIR, OPTIONS);

	return get_and_dump_any_records(h, IB_SA_ATTR_PORTINFORECORD, 0,
					comp_mask, &pir, sizeof(pir),
					dump_one_portinfo_record, p);
}