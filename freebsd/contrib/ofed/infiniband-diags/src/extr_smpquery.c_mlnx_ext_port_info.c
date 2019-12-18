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
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ATTR_MLNX_EXT_PORT_INFO ; 
 int IB_SMP_DATA_SIZE ; 
 int /*<<< orphan*/  mad_dump_mlnx_ext_port_info (char*,int,char*,int) ; 
 char* portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  smp_query_via (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 int strtol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *mlnx_ext_port_info(ib_portid_t * dest, char **argv, int argc)
{
	char buf[2300];
	char data[IB_SMP_DATA_SIZE];
	int portnum = 0;

	if (argc > 0)
		portnum = strtol(argv[0], 0, 0);

	if (!smp_query_via(data, dest, IB_ATTR_MLNX_EXT_PORT_INFO, portnum, 0, srcport))
		return "Mellanox ext port info query failed";

	mad_dump_mlnx_ext_port_info(buf, sizeof buf, data, sizeof data);

	printf("# MLNX ext Port info: %s port %d\n%s", portid2str(dest), portnum, buf);
	return 0;
}