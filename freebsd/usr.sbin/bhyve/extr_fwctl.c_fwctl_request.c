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
typedef  int uint32_t ;
struct TYPE_2__ {int req_count; int req_size; int req_type; int req_txid; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int fwctl_request_data (int) ; 
 int fwctl_request_start () ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ rinfo ; 

__attribute__((used)) static int
fwctl_request(uint32_t value)
{

	int ret;

	ret = 0;

	switch (rinfo.req_count) {
	case 0:
		/* Verify size */
		if (value < 12) {
			printf("msg size error");
			exit(4);
		}
		rinfo.req_size = value;
		rinfo.req_count = 1;
		break;
	case 1:
		rinfo.req_type = value;
		rinfo.req_count++;
		break;
	case 2:
		rinfo.req_txid = value;
		rinfo.req_count++;
		ret = fwctl_request_start();
		break;
	default:
		ret = fwctl_request_data(value);
		break;
	}

	return (ret);
}