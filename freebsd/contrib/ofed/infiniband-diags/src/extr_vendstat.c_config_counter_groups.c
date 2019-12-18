#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_4__ {TYPE_1__* group_selects; } ;
typedef  TYPE_2__ is4_config_counter_groups_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {void* group_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MAD_METHOD_GET ; 
 int /*<<< orphan*/  IB_MAD_METHOD_SET ; 
 int /*<<< orphan*/  IB_MLX_IS4_CONFIG_COUNTER_GROUP ; 
 int /*<<< orphan*/  IB_MLX_VENDOR_CLASS ; 
 int cg0 ; 
 int cg1 ; 
 scalar_t__ do_vendor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int config_counter_groups(ib_portid_t * portid, int port)
{
	char buf[1024];
	is4_config_counter_groups_t *cg_config;

	/* configure counter groups for groups 0 and 1 */
	memset(&buf, 0, sizeof(buf));
	cg_config = (is4_config_counter_groups_t *) & buf;

	printf("counter_groups_config: configuring group0 %d group1 %d\n", cg0,
	       cg1);
	cg_config->group_selects[0].group_select = (uint8_t) cg0;
	cg_config->group_selects[1].group_select = (uint8_t) cg1;

	if (do_vendor(portid, srcport, IB_MLX_VENDOR_CLASS, IB_MAD_METHOD_SET,
		      IB_MLX_IS4_CONFIG_COUNTER_GROUP, port, buf)) {
		fprintf(stderr, "config counter group set failure\n");
		return -1;
	}
	/* get config counter groups */
	memset(&buf, 0, sizeof(buf));

	if (do_vendor(portid, srcport, IB_MLX_VENDOR_CLASS, IB_MAD_METHOD_GET,
		      IB_MLX_IS4_CONFIG_COUNTER_GROUP, port, buf)) {
		fprintf(stderr, "config counter group query failure\n");
		return -1;
	}
	return 0;
}