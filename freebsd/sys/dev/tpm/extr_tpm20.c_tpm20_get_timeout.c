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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  TPM_CC_Create 137 
#define  TPM_CC_CreateLoaded 136 
#define  TPM_CC_CreatePrimary 135 
#define  TPM_CC_EventSequenceComplete 134 
#define  TPM_CC_GetCapability 133 
#define  TPM_CC_HashSequenceStart 132 
#define  TPM_CC_PCR_Extend 131 
#define  TPM_CC_SequenceComplete 130 
#define  TPM_CC_SequenceUpdate 129 
#define  TPM_CC_Startup 128 
 int /*<<< orphan*/  TPM_TIMEOUT_B ; 
 int /*<<< orphan*/  TPM_TIMEOUT_C ; 
 int /*<<< orphan*/  TPM_TIMEOUT_LONG ; 

int32_t
tpm20_get_timeout(uint32_t command)
{
	int32_t timeout;

	switch (command) {
		case TPM_CC_CreatePrimary:
		case TPM_CC_Create:
		case TPM_CC_CreateLoaded:
			timeout = TPM_TIMEOUT_LONG;
			break;
		case TPM_CC_SequenceComplete:
		case TPM_CC_Startup:
		case TPM_CC_SequenceUpdate:
		case TPM_CC_GetCapability:
		case TPM_CC_PCR_Extend:
		case TPM_CC_EventSequenceComplete:
		case TPM_CC_HashSequenceStart:
			timeout = TPM_TIMEOUT_C;
			break;
		default:
			timeout = TPM_TIMEOUT_B;
			break;
	}
	return timeout;
}