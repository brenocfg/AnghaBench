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
typedef  scalar_t__ TNC_IMVID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 void* TNC_TNCS_GetAttribute ; 
 void* TNC_TNCS_ProvideRecommendation ; 
 void* TNC_TNCS_ReportMessageTypes ; 
 void* TNC_TNCS_RequestHandshakeRetry ; 
 void* TNC_TNCS_SendMessage ; 
 void* TNC_TNCS_SetAttribute ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/ * tncs_get_imv (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,char*) ; 

__attribute__((used)) static TNC_Result TNC_TNCS_BindFunction(
	TNC_IMVID imvID,
	char *functionName,
	void **pOutFunctionPointer)
{
	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCS_BindFunction(imcID=%lu, "
		   "functionName='%s')", (unsigned long) imvID, functionName);

	if (tncs_get_imv(imvID) == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	if (pOutFunctionPointer == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	if (os_strcmp(functionName, "TNC_TNCS_ReportMessageTypes") == 0)
		*pOutFunctionPointer = TNC_TNCS_ReportMessageTypes;
	else if (os_strcmp(functionName, "TNC_TNCS_SendMessage") == 0)
		*pOutFunctionPointer = TNC_TNCS_SendMessage;
	else if (os_strcmp(functionName, "TNC_TNCS_RequestHandshakeRetry") ==
		 0)
		*pOutFunctionPointer = TNC_TNCS_RequestHandshakeRetry;
	else if (os_strcmp(functionName, "TNC_TNCS_ProvideRecommendation") ==
		 0)
		*pOutFunctionPointer = TNC_TNCS_ProvideRecommendation;
	else if (os_strcmp(functionName, "TNC_TNCS_GetAttribute") == 0)
		*pOutFunctionPointer = TNC_TNCS_GetAttribute;
	else if (os_strcmp(functionName, "TNC_TNCS_SetAttribute") == 0)
		*pOutFunctionPointer = TNC_TNCS_SetAttribute;
	else
		*pOutFunctionPointer = NULL;

	return TNC_RESULT_SUCCESS;
}