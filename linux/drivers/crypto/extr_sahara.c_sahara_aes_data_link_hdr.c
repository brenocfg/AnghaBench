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
struct sahara_dev {int dummy; } ;

/* Variables and functions */
 int SAHARA_HDR_BASE ; 
 int SAHARA_HDR_CHA_SKHA ; 
 int SAHARA_HDR_FORM_DATA ; 
 int SAHARA_HDR_PARITY_BIT ; 

__attribute__((used)) static u32 sahara_aes_data_link_hdr(struct sahara_dev *dev)
{
	return SAHARA_HDR_BASE | SAHARA_HDR_FORM_DATA |
			SAHARA_HDR_CHA_SKHA | SAHARA_HDR_PARITY_BIT;
}