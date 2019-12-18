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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  seed ;

/* Variables and functions */
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  fnv_32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

uint32_t
m_ether_tcpip_hash_init(void)
{
	uint32_t seed;

	seed = arc4random();
	return (fnv_32_buf(&seed, sizeof(seed), FNV1_32_INIT));
}