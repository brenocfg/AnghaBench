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

/* Variables and functions */
 int ECORE_CRC32_LE (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 

__attribute__((used)) static inline uint8_t ecore_mcast_bin_from_mac(uint8_t *mac)
{
	return (ECORE_CRC32_LE(0, mac, ETH_ALEN) >> 24) & 0xff;
}