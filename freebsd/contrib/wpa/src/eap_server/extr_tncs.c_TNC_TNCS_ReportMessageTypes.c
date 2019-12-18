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
struct tnc_if_imv {size_t num_supported_types; int /*<<< orphan*/ * supported_types; } ;
typedef  size_t TNC_UInt32 ;
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  unsigned long* TNC_MessageTypeList ;
typedef  int /*<<< orphan*/  TNC_MessageType ;
typedef  scalar_t__ TNC_IMVID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TNC_RESULT_FATAL ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (unsigned long*,size_t) ; 
 struct tnc_if_imv* tncs_get_imv (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,size_t,unsigned long) ; 

__attribute__((used)) static TNC_Result TNC_TNCS_ReportMessageTypes(
	TNC_IMVID imvID,
	TNC_MessageTypeList supportedTypes,
	TNC_UInt32 typeCount)
{
	TNC_UInt32 i;
	struct tnc_if_imv *imv;

	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCS_ReportMessageTypes(imvID=%lu "
		   "typeCount=%lu)",
		   (unsigned long) imvID, (unsigned long) typeCount);

	for (i = 0; i < typeCount; i++) {
		wpa_printf(MSG_DEBUG, "TNC: supportedTypes[%lu] = %lu",
			   i, supportedTypes[i]);
	}

	imv = tncs_get_imv(imvID);
	if (imv == NULL)
		return TNC_RESULT_INVALID_PARAMETER;
	os_free(imv->supported_types);
	imv->supported_types = os_memdup(supportedTypes,
					 typeCount * sizeof(TNC_MessageType));
	if (imv->supported_types == NULL)
		return TNC_RESULT_FATAL;
	imv->num_supported_types = typeCount;

	return TNC_RESULT_SUCCESS;
}