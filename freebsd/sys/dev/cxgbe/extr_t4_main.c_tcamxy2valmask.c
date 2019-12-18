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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int htobe64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
tcamxy2valmask(uint64_t x, uint64_t y, uint8_t *addr, uint64_t *mask)
{
	*mask = x | y;
	y = htobe64(y);
	memcpy(addr, (char *)&y + 2, ETHER_ADDR_LEN);
}