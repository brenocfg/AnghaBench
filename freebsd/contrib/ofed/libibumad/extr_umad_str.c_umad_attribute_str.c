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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  UMAD_CLASS_CM 131 
#define  UMAD_CLASS_SUBN_ADM 130 
#define  UMAD_CLASS_SUBN_DIRECTED_ROUTE 129 
#define  UMAD_CLASS_SUBN_LID_ROUTED 128 
 char const* umad_cm_attr_str (int /*<<< orphan*/ ) ; 
 char const* umad_common_attr_str (int /*<<< orphan*/ ) ; 
 char const* umad_sa_attr_str (int /*<<< orphan*/ ) ; 
 char const* umad_sm_attr_str (int /*<<< orphan*/ ) ; 

const char * umad_attribute_str(uint8_t mgmt_class, __be16 attr_id)
{
	switch (mgmt_class) {
		case UMAD_CLASS_SUBN_LID_ROUTED:
		case UMAD_CLASS_SUBN_DIRECTED_ROUTE:
			return(umad_sm_attr_str(attr_id));
		case UMAD_CLASS_SUBN_ADM:
			return(umad_sa_attr_str(attr_id));
		case UMAD_CLASS_CM:
			return(umad_cm_attr_str(attr_id));
	}

	return (umad_common_attr_str(attr_id));
}