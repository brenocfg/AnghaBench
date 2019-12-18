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
struct tnc_if_imc {unsigned char* imc_send; scalar_t__ imc_send_len; } ;
typedef  int /*<<< orphan*/  TNC_UInt32 ;
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  scalar_t__ TNC_MessageType ;
typedef  size_t TNC_IMCID ;
typedef  int /*<<< orphan*/  TNC_ConnectionID ;
typedef  int /*<<< orphan*/  TNC_BufferReference ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t TNC_MAX_IMC_ID ; 
 int /*<<< orphan*/  TNC_RESULT_FATAL ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_OTHER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 unsigned char* base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 scalar_t__ os_snprintf (char*,size_t,char*,unsigned int,unsigned char*) ; 
 unsigned char* os_zalloc (size_t) ; 
 struct tnc_if_imc** tnc_imc ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static TNC_Result TNC_TNCC_SendMessage(
	TNC_IMCID imcID,
	TNC_ConnectionID connectionID,
	TNC_BufferReference message,
	TNC_UInt32 messageLength,
	TNC_MessageType messageType)
{
	struct tnc_if_imc *imc;
	unsigned char *b64;
	size_t b64len;

	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCC_SendMessage(imcID=%lu "
		   "connectionID=%lu messageType=%lu)",
		   imcID, connectionID, messageType);
	wpa_hexdump_ascii(MSG_DEBUG, "TNC: TNC_TNCC_SendMessage",
			  message, messageLength);

	if (imcID >= TNC_MAX_IMC_ID || tnc_imc[imcID] == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	b64 = base64_encode(message, messageLength, &b64len);
	if (b64 == NULL)
		return TNC_RESULT_FATAL;

	imc = tnc_imc[imcID];
	os_free(imc->imc_send);
	imc->imc_send_len = 0;
	imc->imc_send = os_zalloc(b64len + 100);
	if (imc->imc_send == NULL) {
		os_free(b64);
		return TNC_RESULT_OTHER;
	}

	imc->imc_send_len =
		os_snprintf((char *) imc->imc_send, b64len + 100,
			    "<IMC-IMV-Message><Type>%08X</Type>"
			    "<Base64>%s</Base64></IMC-IMV-Message>",
			    (unsigned int) messageType, b64);

	os_free(b64);

	return TNC_RESULT_SUCCESS;
}