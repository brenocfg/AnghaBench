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
typedef  int /*<<< orphan*/  const u8 ;
typedef  size_t u32 ;

/* Variables and functions */
#define  FLYBY_2SRC_XOR 131 
#define  FLYBY_3SRC_XOR 130 
#define  FLYBY_4SRC_XOR 129 
#define  FLYBY_5SRC_XOR 128 

__attribute__((used)) static u8 xgene_dma_encode_xor_flyby(u32 src_cnt)
{
	static u8 flyby_type[] = {
		FLYBY_2SRC_XOR, /* Dummy */
		FLYBY_2SRC_XOR, /* Dummy */
		FLYBY_2SRC_XOR,
		FLYBY_3SRC_XOR,
		FLYBY_4SRC_XOR,
		FLYBY_5SRC_XOR
	};

	return flyby_type[src_cnt];
}