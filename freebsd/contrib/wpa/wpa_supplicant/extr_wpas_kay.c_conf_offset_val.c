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
typedef  enum confidentiality_offset { ____Placeholder_confidentiality_offset } confidentiality_offset ;

/* Variables and functions */
#define  CONFIDENTIALITY_OFFSET_30 129 
#define  CONFIDENTIALITY_OFFSET_50 128 

__attribute__((used)) static unsigned int conf_offset_val(enum confidentiality_offset co)
{
	switch (co) {
	case CONFIDENTIALITY_OFFSET_30:
		return 30;
		break;
	case CONFIDENTIALITY_OFFSET_50:
		return 50;
	default:
		return 0;
	}
}