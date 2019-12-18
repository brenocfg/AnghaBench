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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 void* DC_SP_MAC (int) ; 
 scalar_t__ DC_ULI_FILTER_NPERF ; 
 int* LLADDR (struct sockaddr_dl*) ; 

__attribute__((used)) static u_int
dc_hash_maddr_uli(void *arg, struct sockaddr_dl *sdl, u_int mcnt)
{
	uint32_t **sp = arg;
	uint8_t *ma;

	if (mcnt == DC_ULI_FILTER_NPERF)
		return (0);
	ma = LLADDR(sdl);
	*(*sp)++ = DC_SP_MAC(ma[1] << 8 | ma[0]);
	*(*sp)++ = DC_SP_MAC(ma[3] << 8 | ma[2]);
	*(*sp)++ = DC_SP_MAC(ma[5] << 8 | ma[4]);

	return (1);
}