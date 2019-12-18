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

/* Variables and functions */
 int CONFIG_ECORE_FCOE_BITMAP_IDX ; 
 int CONFIG_ECORE_ISCSI_BITMAP_IDX ; 
 int CONFIG_ECORE_IWARP_BITMAP_IDX ; 
 int CONFIG_ECORE_L2_BITMAP_IDX ; 
 int CONFIG_ECORE_LL2_BITMAP_IDX ; 
 int CONFIG_ECORE_ROCE_BITMAP_IDX ; 
 int CONFIG_ECORE_SRIOV_BITMAP_IDX ; 

__attribute__((used)) static u32 ecore_get_config_bitmap(void)
{
	u32 config_bitmap = 0x0;

#ifdef CONFIG_ECORE_L2
	config_bitmap |= CONFIG_ECORE_L2_BITMAP_IDX;
#endif
#ifdef CONFIG_ECORE_SRIOV
	config_bitmap |= CONFIG_ECORE_SRIOV_BITMAP_IDX;
#endif
#ifdef CONFIG_ECORE_ROCE
	config_bitmap |= CONFIG_ECORE_ROCE_BITMAP_IDX;
#endif
#ifdef CONFIG_ECORE_IWARP
	config_bitmap |= CONFIG_ECORE_IWARP_BITMAP_IDX;
#endif
#ifdef CONFIG_ECORE_FCOE
	config_bitmap |= CONFIG_ECORE_FCOE_BITMAP_IDX;
#endif
#ifdef CONFIG_ECORE_ISCSI
	config_bitmap |= CONFIG_ECORE_ISCSI_BITMAP_IDX;
#endif
#ifdef CONFIG_ECORE_LL2
	config_bitmap |= CONFIG_ECORE_LL2_BITMAP_IDX;
#endif

	return config_bitmap;
}