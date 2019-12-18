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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
typedef  TYPE_1__ t_FmPhysAddr ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void SET_ADDR(volatile t_FmPhysAddr *fmPhysAddr, uint64_t value)
{
    WRITE_UINT8(fmPhysAddr->high,(uint8_t)((value & 0x000000ff00000000LL) >> 32));
    WRITE_UINT32(fmPhysAddr->low,(uint32_t)value);
}