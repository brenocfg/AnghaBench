#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {void* ih_hcrc; void* ih_size; void* ih_dcrc; } ;
typedef  TYPE_1__ image_header_t ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* htonl (int) ; 

void
calc_crc(image_header_t *hdr, void *data, uint32_t len)
{
	/*
	 * Calculate payload checksum
	 */
	hdr->ih_dcrc = htonl(crc32(0, (Bytef *)data, len));
	hdr->ih_size = htonl(len);
	/*
	 * Calculate header checksum
	 */
	hdr->ih_hcrc = 0;
	hdr->ih_hcrc = htonl(crc32(0, (Bytef *)hdr, sizeof(image_header_t)));
}