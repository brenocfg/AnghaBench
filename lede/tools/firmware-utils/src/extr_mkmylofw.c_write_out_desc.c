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
typedef  int /*<<< orphan*/  uint32_t ;
struct mylo_fw_blockdesc {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
write_out_desc(FILE *outfile, struct mylo_fw_blockdesc *desc, uint32_t *crc)
{
	return write_out_data(outfile, (uint8_t *)desc,
		sizeof(*desc), crc);
}