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
struct rite_binary_header {scalar_t__ binary_crc; } ;

/* Variables and functions */

__attribute__((used)) static size_t
offset_crc_body(void)
{
  struct rite_binary_header header;
  return ((uint8_t *)header.binary_crc - (uint8_t *)&header) + sizeof(header.binary_crc);
}