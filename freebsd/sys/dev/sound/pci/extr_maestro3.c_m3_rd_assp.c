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
typedef  int u_int16_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_PORT_MEMORY_DATA ; 
 int /*<<< orphan*/  DSP_PORT_MEMORY_INDEX ; 
 int /*<<< orphan*/  DSP_PORT_MEMORY_TYPE ; 
 int MEMTYPE_MASK ; 
 int m3_rd_2 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_wr_2 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline u_int16_t
m3_rd_assp(struct sc_info *sc, u_int16_t region, u_int16_t index)
{
        m3_wr_2(sc, DSP_PORT_MEMORY_TYPE, region & MEMTYPE_MASK);
        m3_wr_2(sc, DSP_PORT_MEMORY_INDEX, index);
        return m3_rd_2(sc, DSP_PORT_MEMORY_DATA);
}