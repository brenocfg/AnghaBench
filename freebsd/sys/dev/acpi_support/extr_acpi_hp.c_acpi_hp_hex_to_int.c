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
typedef  unsigned int UINT8 ;

/* Variables and functions */

__attribute__((used)) static __inline int acpi_hp_hex_to_int(const UINT8 *hexin, UINT8 *byteout)
{
	unsigned int	hi;
	unsigned int	lo;

	hi = hexin[0];
	lo = hexin[1];
	if ('0' <= hi && hi <= '9')
		hi -= '0';
	else if ('A' <= hi && hi <= 'F')
		hi -= ('A' - 10);
	else if ('a' <= hi && hi <= 'f')
		hi -= ('a' - 10);
	else
		return (1);
	if ('0' <= lo && lo <= '9')
		lo -= '0';
	else if ('A' <= lo && lo <= 'F')
		lo -= ('A' - 10);
	else if ('a' <= lo && lo <= 'f')
		lo -= ('a' - 10);
	else
		return (1);
	*byteout = (hi << 4) + lo;

	return (0);
}