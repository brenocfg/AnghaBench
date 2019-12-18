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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int SMBIOS_GET8 (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static uint8_t
smbios_checksum(const caddr_t addr, const uint8_t len)
{
	uint8_t		sum;
	int		i;

	for (sum = 0, i = 0; i < len; i++)
		sum += SMBIOS_GET8(addr, i);
	return (sum);
}