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
struct fw_header {void* flags; void* firmware_len; void* hw_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_FLAGS ; 
 void* HOST_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_len ; 
 int /*<<< orphan*/  hw_id ; 
 int /*<<< orphan*/  memset (struct fw_header*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_header(uint8_t *buf)
{
	struct fw_header *hdr = (struct fw_header *) buf;

	memset(hdr, 0, sizeof (struct fw_header));
	hdr->hw_id = HOST_TO_LE32(hw_id);
	hdr->firmware_len = HOST_TO_LE32(firmware_len);
	hdr->flags = HOST_TO_LE32(HEADER_FLAGS);
}