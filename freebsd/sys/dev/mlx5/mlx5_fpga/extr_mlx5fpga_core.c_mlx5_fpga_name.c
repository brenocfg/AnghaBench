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
typedef  int u32 ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
#define  MLX5_FPGA_EDISON 131 
#define  MLX5_FPGA_MORSE 130 
#define  MLX5_FPGA_MORSEQ 129 
#define  MLX5_FPGA_NEWTON 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *mlx5_fpga_name(u32 fpga_id)
{
	static char ret[32];

	switch (fpga_id) {
	case MLX5_FPGA_NEWTON:
		return "Newton";
	case MLX5_FPGA_EDISON:
		return "Edison";
	case MLX5_FPGA_MORSE:
		return "Morse";
	case MLX5_FPGA_MORSEQ:
		return "MorseQ";
	}

	snprintf(ret, sizeof(ret), "Unknown %d", fpga_id);
	return ret;
}