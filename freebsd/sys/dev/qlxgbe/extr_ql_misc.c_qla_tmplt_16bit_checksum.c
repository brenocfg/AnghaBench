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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t
qla_tmplt_16bit_checksum(qla_host_t *ha, uint16_t *buf, uint32_t size)
{
	uint32_t sum = 0;
	uint32_t count = size >> 1; /* size in 16 bit words */

	while (count-- > 0) 
		sum += *buf++;

	while (sum >> 16) 
		sum = (sum & 0xFFFF) + (sum >> 16);

	return (~sum);
}