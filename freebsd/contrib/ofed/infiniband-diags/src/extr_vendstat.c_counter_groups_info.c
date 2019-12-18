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
struct TYPE_2__ {int num_of_counter_groups; int /*<<< orphan*/ * group_masks; } ;
typedef  TYPE_1__ is4_counter_group_info_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MAD_METHOD_GET ; 
 int /*<<< orphan*/  IB_MLX_IS4_COUNTER_GROUP_INFO ; 
 int /*<<< orphan*/  IB_MLX_VENDOR_CLASS ; 
 scalar_t__ do_vendor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int counter_groups_info(ib_portid_t * portid, int port)
{
	char buf[1024];
	is4_counter_group_info_t *cg_info;
	int i, num_cg;

	/* Counter Group Info */
	memset(&buf, 0, sizeof(buf));
	if (do_vendor(portid, srcport, IB_MLX_VENDOR_CLASS, IB_MAD_METHOD_GET,
		      IB_MLX_IS4_COUNTER_GROUP_INFO, port, buf)) {
		fprintf(stderr,"counter group info query failure\n");
		return -1;
	}
	cg_info = (is4_counter_group_info_t *) & buf;
	num_cg = cg_info->num_of_counter_groups;
	printf("counter_group_info:\n");
	printf("%d counter groups\n", num_cg);
	for (i = 0; i < num_cg; i++)
		printf("group%d mask %#x\n", i, ntohl(cg_info->group_masks[i]));
	return 0;
}