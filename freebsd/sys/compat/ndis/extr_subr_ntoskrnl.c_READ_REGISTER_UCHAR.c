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
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_BUS_SPACE_MEM ; 
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
READ_REGISTER_UCHAR(uint8_t *reg)
{
	return (bus_space_read_1(NDIS_BUS_SPACE_MEM, 0x0, (bus_size_t)reg));
}