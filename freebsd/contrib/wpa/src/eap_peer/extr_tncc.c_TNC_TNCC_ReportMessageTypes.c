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
struct tnc_if_imc {size_t num_supported_types; int /*<<< orphan*/ * supported_types; } ;
typedef  size_t TNC_UInt32 ;
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  unsigned long* TNC_MessageTypeList ;
typedef  int /*<<< orphan*/  TNC_MessageType ;
typedef  size_t TNC_IMCID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t TNC_MAX_IMC_ID ; 
 int /*<<< orphan*/  TNC_RESULT_FATAL ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (unsigned long*,size_t) ; 
 struct tnc_if_imc** tnc_imc ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,size_t,unsigned long) ; 

__attribute__((used)) static TNC_Result TNC_TNCC_ReportMessageTypes(
	TNC_IMCID imcID,
	TNC_MessageTypeList supportedTypes,
	TNC_UInt32 typeCount)
{
	TNC_UInt32 i;
	struct tnc_if_imc *imc;

	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCC_ReportMessageTypes(imcID=%lu "
		   "typeCount=%lu)",
		   (unsigned long) imcID, (unsigned long) typeCount);

	for (i = 0; i < typeCount; i++) {
		wpa_printf(MSG_DEBUG, "TNC: supportedTypes[%lu] = %lu",
			   i, supportedTypes[i]);
	}

	if (imcID >= TNC_MAX_IMC_ID || tnc_imc[imcID] == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	imc = tnc_imc[imcID];
	os_free(imc->supported_types);
	imc->supported_types = os_memdup(supportedTypes,
					 typeCount * sizeof(TNC_MessageType));
	if (imc->supported_types == NULL)
		return TNC_RESULT_FATAL;
	imc->num_supported_types = typeCount;

	return TNC_RESULT_SUCCESS;
}