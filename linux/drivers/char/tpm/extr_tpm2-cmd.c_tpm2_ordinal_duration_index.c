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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
#define  TPM2_CC_CREATE 143 
#define  TPM2_CC_CREATE_LOADED 142 
#define  TPM2_CC_CREATE_PRIMARY 141 
#define  TPM2_CC_EVENT_SEQUENCE_COMPLETE 140 
#define  TPM2_CC_GET_CAPABILITY 139 
#define  TPM2_CC_GET_RANDOM 138 
#define  TPM2_CC_HASH_SEQUENCE_START 137 
#define  TPM2_CC_HIERARCHY_CHANGE_AUTH 136 
#define  TPM2_CC_HIERARCHY_CONTROL 135 
#define  TPM2_CC_NV_READ 134 
#define  TPM2_CC_PCR_EXTEND 133 
#define  TPM2_CC_SELF_TEST 132 
#define  TPM2_CC_SEQUENCE_COMPLETE 131 
#define  TPM2_CC_SEQUENCE_UPDATE 130 
#define  TPM2_CC_STARTUP 129 
#define  TPM2_CC_VERIFY_SIGNATURE 128 
 int /*<<< orphan*/  TPM_LONG ; 
 int /*<<< orphan*/  TPM_LONG_LONG ; 
 int /*<<< orphan*/  TPM_MEDIUM ; 
 int /*<<< orphan*/  TPM_UNDEFINED ; 

__attribute__((used)) static u8 tpm2_ordinal_duration_index(u32 ordinal)
{
	switch (ordinal) {
	/* Startup */
	case TPM2_CC_STARTUP:                 /* 144 */
		return TPM_MEDIUM;

	case TPM2_CC_SELF_TEST:               /* 143 */
		return TPM_LONG;

	case TPM2_CC_GET_RANDOM:              /* 17B */
		return TPM_LONG;

	case TPM2_CC_SEQUENCE_UPDATE:         /* 15C */
		return TPM_MEDIUM;
	case TPM2_CC_SEQUENCE_COMPLETE:       /* 13E */
		return TPM_MEDIUM;
	case TPM2_CC_EVENT_SEQUENCE_COMPLETE: /* 185 */
		return TPM_MEDIUM;
	case TPM2_CC_HASH_SEQUENCE_START:     /* 186 */
		return TPM_MEDIUM;

	case TPM2_CC_VERIFY_SIGNATURE:        /* 177 */
		return TPM_LONG;

	case TPM2_CC_PCR_EXTEND:              /* 182 */
		return TPM_MEDIUM;

	case TPM2_CC_HIERARCHY_CONTROL:       /* 121 */
		return TPM_LONG;
	case TPM2_CC_HIERARCHY_CHANGE_AUTH:   /* 129 */
		return TPM_LONG;

	case TPM2_CC_GET_CAPABILITY:          /* 17A */
		return TPM_MEDIUM;

	case TPM2_CC_NV_READ:                 /* 14E */
		return TPM_LONG;

	case TPM2_CC_CREATE_PRIMARY:          /* 131 */
		return TPM_LONG_LONG;
	case TPM2_CC_CREATE:                  /* 153 */
		return TPM_LONG_LONG;
	case TPM2_CC_CREATE_LOADED:           /* 191 */
		return TPM_LONG_LONG;

	default:
		return TPM_UNDEFINED;
	}
}