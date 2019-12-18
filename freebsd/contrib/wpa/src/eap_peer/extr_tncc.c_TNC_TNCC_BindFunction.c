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
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  size_t TNC_IMCID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TNC_9048_LogMessage ; 
 void* TNC_9048_UserMessage ; 
 size_t TNC_MAX_IMC_ID ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 void* TNC_TNCC_ReportMessageTypes ; 
 void* TNC_TNCC_RequestHandshakeRetry ; 
 void* TNC_TNCC_SendMessage ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/ ** tnc_imc ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,char*) ; 

__attribute__((used)) static TNC_Result TNC_TNCC_BindFunction(
	TNC_IMCID imcID,
	char *functionName,
	void **pOutfunctionPointer)
{
	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCC_BindFunction(imcID=%lu, "
		   "functionName='%s')", (unsigned long) imcID, functionName);

	if (imcID >= TNC_MAX_IMC_ID || tnc_imc[imcID] == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	if (pOutfunctionPointer == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	if (os_strcmp(functionName, "TNC_TNCC_ReportMessageTypes") == 0)
		*pOutfunctionPointer = TNC_TNCC_ReportMessageTypes;
	else if (os_strcmp(functionName, "TNC_TNCC_SendMessage") == 0)
		*pOutfunctionPointer = TNC_TNCC_SendMessage;
	else if (os_strcmp(functionName, "TNC_TNCC_RequestHandshakeRetry") ==
		 0)
		*pOutfunctionPointer = TNC_TNCC_RequestHandshakeRetry;
	else if (os_strcmp(functionName, "TNC_9048_LogMessage") == 0)
		*pOutfunctionPointer = TNC_9048_LogMessage;
	else if (os_strcmp(functionName, "TNC_9048_UserMessage") == 0)
		*pOutfunctionPointer = TNC_9048_UserMessage;
	else
		*pOutfunctionPointer = NULL;

	return TNC_RESULT_SUCCESS;
}