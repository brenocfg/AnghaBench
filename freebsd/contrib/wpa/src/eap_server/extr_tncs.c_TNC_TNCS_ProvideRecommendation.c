#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tncs_data {TYPE_1__* imv_data; } ;
struct TYPE_2__ {int recommendation_set; scalar_t__ recommendation; } ;
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  scalar_t__ TNC_IMV_Evaluation_Result ;
typedef  scalar_t__ TNC_IMV_Action_Recommendation ;
typedef  size_t TNC_IMVID ;
typedef  scalar_t__ TNC_ConnectionID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TNC_RESULT_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 struct tncs_data* tncs_get_conn (scalar_t__) ; 
 int /*<<< orphan*/ * tncs_get_imv (size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static TNC_Result TNC_TNCS_ProvideRecommendation(
	TNC_IMVID imvID,
	TNC_ConnectionID connectionID,
	TNC_IMV_Action_Recommendation recommendation,
	TNC_IMV_Evaluation_Result evaluation)
{
	struct tncs_data *tncs;

	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCS_ProvideRecommendation(imvID=%lu "
		   "connectionID=%lu recommendation=%lu evaluation=%lu)",
		   (unsigned long) imvID, (unsigned long) connectionID,
		   (unsigned long) recommendation, (unsigned long) evaluation);

	if (tncs_get_imv(imvID) == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	tncs = tncs_get_conn(connectionID);
	if (tncs == NULL)
		return TNC_RESULT_INVALID_PARAMETER;

	tncs->imv_data[imvID].recommendation = recommendation;
	tncs->imv_data[imvID].recommendation_set = 1;

	return TNC_RESULT_SUCCESS;
}