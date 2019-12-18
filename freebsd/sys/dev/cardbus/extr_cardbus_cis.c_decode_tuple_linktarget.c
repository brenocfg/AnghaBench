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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tuple_callbacks {char* name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cardbus_cis_debug ; 
 int /*<<< orphan*/  decode_tuple_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tuple_callbacks*,void*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
decode_tuple_linktarget(device_t cbdev, device_t child, int id,
    int len, uint8_t *tupledata, uint32_t start, uint32_t *off,
    struct tuple_callbacks *info, void *argp)
{
	int i;

	if (cardbus_cis_debug) {
		printf("TUPLE: %s [%d]:", info->name, len);

		for (i = 0; i < len; i++) {
			if (i % 0x10 == 0 && len > 0x10)
				printf("\n       0x%02x:", i);
			printf(" %02x", tupledata[i]);
		}
		printf("\n");
	}
	if (len != 3 || tupledata[0] != 'C' || tupledata[1] != 'I' ||
	    tupledata[2] != 'S') {
		printf("Invalid data for CIS Link Target!\n");
		decode_tuple_generic(cbdev, child, id, len, tupledata,
		    start, off, info, argp);
		return (EINVAL);
	}
	return (0);
}