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
struct adf_hw_device_data {int fuses; } ;
typedef  enum dev_sku_info { ____Placeholder_dev_sku_info } dev_sku_info ;

/* Variables and functions */
#define  ADF_DH895XCC_FUSECTL_SKU_1 131 
#define  ADF_DH895XCC_FUSECTL_SKU_2 130 
#define  ADF_DH895XCC_FUSECTL_SKU_3 129 
#define  ADF_DH895XCC_FUSECTL_SKU_4 128 
 int ADF_DH895XCC_FUSECTL_SKU_MASK ; 
 int ADF_DH895XCC_FUSECTL_SKU_SHIFT ; 
 int DEV_SKU_1 ; 
 int DEV_SKU_2 ; 
 int DEV_SKU_3 ; 
 int DEV_SKU_4 ; 
 int DEV_SKU_UNKNOWN ; 

__attribute__((used)) static enum dev_sku_info get_sku(struct adf_hw_device_data *self)
{
	int sku = (self->fuses & ADF_DH895XCC_FUSECTL_SKU_MASK)
	    >> ADF_DH895XCC_FUSECTL_SKU_SHIFT;

	switch (sku) {
	case ADF_DH895XCC_FUSECTL_SKU_1:
		return DEV_SKU_1;
	case ADF_DH895XCC_FUSECTL_SKU_2:
		return DEV_SKU_2;
	case ADF_DH895XCC_FUSECTL_SKU_3:
		return DEV_SKU_3;
	case ADF_DH895XCC_FUSECTL_SKU_4:
		return DEV_SKU_4;
	default:
		return DEV_SKU_UNKNOWN;
	}
	return DEV_SKU_UNKNOWN;
}