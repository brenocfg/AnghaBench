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
struct media {scalar_t__ baudrate; int subtype; } ;

/* Variables and functions */
 int IFM_10G_ER ; 
#define  IFM_10G_LR 129 
#define  IFM_40G_ER4 128 
 int IFM_40G_LR4 ; 
 int MLX5E_EXT_LINK_SPEEDS_NUMBER ; 
 int MLX5E_LINK_MODES_NUMBER ; 
 int MLX5E_LINK_SPEEDS_NUMBER ; 
 int MLX5E_PROT_MASK (int) ; 
 struct media** mlx5e_ext_mode_table ; 
 struct media** mlx5e_mode_table ; 

__attribute__((used)) static u32
mlx5e_find_link_mode(u32 subtype, bool ext)
{
	u32 i;
	u32 j;
	u32 link_mode = 0;
	u32 speeds_num = 0;
	struct media media_entry = {};

	switch (subtype) {
	case IFM_10G_LR:
		subtype = IFM_10G_ER;
		break;
	case IFM_40G_ER4:
		subtype = IFM_40G_LR4;
		break;
	}

	speeds_num = ext ? MLX5E_EXT_LINK_SPEEDS_NUMBER :
	    MLX5E_LINK_SPEEDS_NUMBER;

	for (i = 0; i != speeds_num; i++) {
		for (j = 0; j < MLX5E_LINK_MODES_NUMBER ; ++j) {
			media_entry = ext ? mlx5e_ext_mode_table[i][j] :
			    mlx5e_mode_table[i][j];
			if (media_entry.baudrate == 0)
				continue;
			if (media_entry.subtype == subtype) {
				link_mode |= MLX5E_PROT_MASK(i);
			}
		}
	}

	return (link_mode);
}