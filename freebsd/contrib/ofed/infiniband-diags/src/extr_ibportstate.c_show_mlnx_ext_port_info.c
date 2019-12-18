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
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_DATA_SIZE ; 
 int /*<<< orphan*/  mad_dump_mlnx_ext_port_info (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 

__attribute__((used)) static void show_mlnx_ext_port_info(ib_portid_t * dest, uint8_t * data, int portnum)
{
	char buf[256];

	mad_dump_mlnx_ext_port_info(buf, sizeof buf, data, IB_SMP_DATA_SIZE);

	printf("# MLNX ext Port info: %s port %d\n%s", portid2str(dest),
	       portnum, buf);
}