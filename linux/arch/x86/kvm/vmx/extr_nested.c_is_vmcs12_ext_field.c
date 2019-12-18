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

/* Variables and functions */
#define  GUEST_BNDCFGS 163 
#define  GUEST_CS_BASE 162 
#define  GUEST_CS_LIMIT 161 
#define  GUEST_CS_SELECTOR 160 
#define  GUEST_DS_AR_BYTES 159 
#define  GUEST_DS_BASE 158 
#define  GUEST_DS_LIMIT 157 
#define  GUEST_DS_SELECTOR 156 
#define  GUEST_ES_AR_BYTES 155 
#define  GUEST_ES_BASE 154 
#define  GUEST_ES_LIMIT 153 
#define  GUEST_ES_SELECTOR 152 
#define  GUEST_FS_AR_BYTES 151 
#define  GUEST_FS_BASE 150 
#define  GUEST_FS_LIMIT 149 
#define  GUEST_FS_SELECTOR 148 
#define  GUEST_GDTR_BASE 147 
#define  GUEST_GDTR_LIMIT 146 
#define  GUEST_GS_AR_BYTES 145 
#define  GUEST_GS_BASE 144 
#define  GUEST_GS_LIMIT 143 
#define  GUEST_GS_SELECTOR 142 
#define  GUEST_IDTR_BASE 141 
#define  GUEST_IDTR_LIMIT 140 
#define  GUEST_LDTR_AR_BYTES 139 
#define  GUEST_LDTR_BASE 138 
#define  GUEST_LDTR_LIMIT 137 
#define  GUEST_LDTR_SELECTOR 136 
#define  GUEST_PENDING_DBG_EXCEPTIONS 135 
#define  GUEST_SS_BASE 134 
#define  GUEST_SS_LIMIT 133 
#define  GUEST_SS_SELECTOR 132 
#define  GUEST_TR_AR_BYTES 131 
#define  GUEST_TR_BASE 130 
#define  GUEST_TR_LIMIT 129 
#define  GUEST_TR_SELECTOR 128 

__attribute__((used)) static bool is_vmcs12_ext_field(unsigned long field)
{
	switch (field) {
	case GUEST_ES_SELECTOR:
	case GUEST_CS_SELECTOR:
	case GUEST_SS_SELECTOR:
	case GUEST_DS_SELECTOR:
	case GUEST_FS_SELECTOR:
	case GUEST_GS_SELECTOR:
	case GUEST_LDTR_SELECTOR:
	case GUEST_TR_SELECTOR:
	case GUEST_ES_LIMIT:
	case GUEST_CS_LIMIT:
	case GUEST_SS_LIMIT:
	case GUEST_DS_LIMIT:
	case GUEST_FS_LIMIT:
	case GUEST_GS_LIMIT:
	case GUEST_LDTR_LIMIT:
	case GUEST_TR_LIMIT:
	case GUEST_GDTR_LIMIT:
	case GUEST_IDTR_LIMIT:
	case GUEST_ES_AR_BYTES:
	case GUEST_DS_AR_BYTES:
	case GUEST_FS_AR_BYTES:
	case GUEST_GS_AR_BYTES:
	case GUEST_LDTR_AR_BYTES:
	case GUEST_TR_AR_BYTES:
	case GUEST_ES_BASE:
	case GUEST_CS_BASE:
	case GUEST_SS_BASE:
	case GUEST_DS_BASE:
	case GUEST_FS_BASE:
	case GUEST_GS_BASE:
	case GUEST_LDTR_BASE:
	case GUEST_TR_BASE:
	case GUEST_GDTR_BASE:
	case GUEST_IDTR_BASE:
	case GUEST_PENDING_DBG_EXCEPTIONS:
	case GUEST_BNDCFGS:
		return true;
	default:
		break;
	}

	return false;
}