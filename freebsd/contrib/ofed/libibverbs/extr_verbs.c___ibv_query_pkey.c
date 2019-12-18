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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ibv_context {TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  ibdev_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_read_sysfs_file (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *) ; 

int __ibv_query_pkey(struct ibv_context *context, uint8_t port_num,
		     int index, __be16 *pkey)
{
	char name[24];
	char attr[8];
	uint16_t val;

	snprintf(name, sizeof name, "ports/%d/pkeys/%d", port_num, index);

	if (ibv_read_sysfs_file(context->device->ibdev_path, name,
				attr, sizeof attr) < 0)
		return -1;

	if (sscanf(attr, "%hx", &val) != 1)
		return -1;

	*pkey = htobe16(val);
	return 0;
}