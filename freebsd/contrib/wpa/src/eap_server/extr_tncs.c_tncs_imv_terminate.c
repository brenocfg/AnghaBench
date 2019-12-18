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
struct tnc_if_imv {scalar_t__ (* Terminate ) (int /*<<< orphan*/ ) ;unsigned long name; int /*<<< orphan*/  imvID; } ;
typedef  scalar_t__ TNC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ TNC_RESULT_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int tncs_imv_terminate(struct tnc_if_imv *imv)
{
	TNC_Result res;

	if (imv->Terminate == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "TNC: Calling TNC_IMV_Terminate for IMV '%s'",
		   imv->name);
	res = imv->Terminate(imv->imvID);
	wpa_printf(MSG_DEBUG, "TNC: TNC_IMV_Terminate: %lu",
		   (unsigned long) res);

	return res == TNC_RESULT_SUCCESS ? 0 : -1;
}