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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 scalar_t__ AGP_CAPID ; 
 scalar_t__ AGP_MODE_GET_AGP (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_MODE_GET_MODE_3 (int /*<<< orphan*/ ) ; 
 int AGP_MODE_GET_RATE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_MODE_GET_SBA (int /*<<< orphan*/ ) ; 
#define  AGP_MODE_V2_RATE_1x 132 
#define  AGP_MODE_V2_RATE_2x 131 
#define  AGP_MODE_V2_RATE_4x 130 
#define  AGP_MODE_V3_RATE_4x 129 
#define  AGP_MODE_V3_RATE_8x 128 
 scalar_t__ AGP_STATUS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_config (int,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
cap_agp(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint32_t status, command;

	status = read_config(fd, &p->pc_sel, ptr + AGP_STATUS, 4);
	command = read_config(fd, &p->pc_sel, ptr + AGP_CAPID, 4);
	printf("AGP ");
	if (AGP_MODE_GET_MODE_3(status)) {
		printf("v3 ");
		if (AGP_MODE_GET_RATE(status) & AGP_MODE_V3_RATE_8x)
			printf("8x ");
		if (AGP_MODE_GET_RATE(status) & AGP_MODE_V3_RATE_4x)
			printf("4x ");
	} else {
		if (AGP_MODE_GET_RATE(status) & AGP_MODE_V2_RATE_4x)
			printf("4x ");
		if (AGP_MODE_GET_RATE(status) & AGP_MODE_V2_RATE_2x)
			printf("2x ");
		if (AGP_MODE_GET_RATE(status) & AGP_MODE_V2_RATE_1x)
			printf("1x ");
	}
	if (AGP_MODE_GET_SBA(status))
		printf("SBA ");
	if (AGP_MODE_GET_AGP(command)) {
		printf("enabled at ");
		if (AGP_MODE_GET_MODE_3(command)) {
			printf("v3 ");
			switch (AGP_MODE_GET_RATE(command)) {
			case AGP_MODE_V3_RATE_8x:
				printf("8x ");
				break;
			case AGP_MODE_V3_RATE_4x:
				printf("4x ");
				break;
			}
		} else
			switch (AGP_MODE_GET_RATE(command)) {
			case AGP_MODE_V2_RATE_4x:
				printf("4x ");
				break;
			case AGP_MODE_V2_RATE_2x:
				printf("2x ");
				break;
			case AGP_MODE_V2_RATE_1x:
				printf("1x ");
				break;
			}
		if (AGP_MODE_GET_SBA(command))
			printf("SBA ");
	} else
		printf("disabled");
}