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
typedef  int /*<<< orphan*/  TNC_RetryReason ;
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  size_t TNC_IMCID ;
typedef  int /*<<< orphan*/  TNC_ConnectionID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t TNC_MAX_IMC_ID ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 int /*<<< orphan*/ ** tnc_imc ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static TNC_Result TNC_TNCC_RequestHandshakeRetry(
	TNC_IMCID imcID,
	TNC_ConnectionID connectionID,
	TNC_RetryReason reason)
{
	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCC_RequestHandshakeRetry");

	if (imcID >= TNC_MAX_IMC_ID || tnc_imc[imcID] == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	/*
	 * TODO: trigger a call to eapol_sm_request_reauth(). This would
	 * require that the IMC continues to be loaded in memory afer
	 * authentication..
	 */

	return TNC_RESULT_SUCCESS;
}