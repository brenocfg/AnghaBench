#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* record; } ;
typedef  TYPE_2__ is3_config_space_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_5__ {int address; int data; int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MAD_METHOD_GET ; 
 int /*<<< orphan*/  IB_MAD_METHOD_SET ; 
 int /*<<< orphan*/  IB_MLX_IS3_CONFIG_SPACE_ACCESS ; 
 int /*<<< orphan*/  IB_MLX_VENDOR_CLASS ; 
 scalar_t__ do_vendor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 void* htonl (int) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int do_config_space_records(ib_portid_t *portid, unsigned set,
				    is3_config_space_t *cs, unsigned records)
{
	unsigned i;

	if (records > 18)
		records = 18;
	for (i = 0; i < records; i++) {
		cs->record[i].address = htonl(cs->record[i].address);
		cs->record[i].data = htonl(cs->record[i].data);
		cs->record[i].mask = htonl(cs->record[i].mask);
	}

	if (do_vendor(portid, srcport, IB_MLX_VENDOR_CLASS,
		      set ? IB_MAD_METHOD_SET : IB_MAD_METHOD_GET,
		      IB_MLX_IS3_CONFIG_SPACE_ACCESS, 2 << 22 | records << 16,
		      cs)) {
		fprintf(stderr,"cannot %s config space records\n", set ? "set" : "get");
		return -1;
	}
	for (i = 0; i < records; i++) {
		printf("Config space record at 0x%x: 0x%x\n",
		       ntohl(cs->record[i].address),
		       ntohl(cs->record[i].data & cs->record[i].mask));
	}
	return 0;
}