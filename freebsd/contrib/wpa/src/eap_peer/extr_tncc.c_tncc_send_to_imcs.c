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
struct tncc_data {struct tnc_if_imc* imc; } ;
struct tnc_if_imc {unsigned long name; int /*<<< orphan*/  connectionID; int /*<<< orphan*/  imcID; scalar_t__ (* ReceiveMessage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned int) ;struct tnc_if_imc* next; } ;
typedef  scalar_t__ TNC_Result ;
typedef  int /*<<< orphan*/  TNC_BufferReference ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 int /*<<< orphan*/  tncc_supported_type (struct tnc_if_imc*,unsigned int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void tncc_send_to_imcs(struct tncc_data *tncc, unsigned int type,
			      const u8 *msg, size_t len)
{
	struct tnc_if_imc *imc;
	TNC_Result res;

	wpa_hexdump_ascii(MSG_MSGDUMP, "TNC: Message to IMC(s)", msg, len);

	for (imc = tncc->imc; imc; imc = imc->next) {
		if (imc->ReceiveMessage == NULL ||
		    !tncc_supported_type(imc, type))
			continue;

		wpa_printf(MSG_DEBUG, "TNC: Call ReceiveMessage for IMC '%s'",
			   imc->name);
		res = imc->ReceiveMessage(imc->imcID, imc->connectionID,
					  (TNC_BufferReference) msg, len,
					  type);
		wpa_printf(MSG_DEBUG, "TNC: ReceiveMessage: %lu",
			   (unsigned long) res);
	}
}