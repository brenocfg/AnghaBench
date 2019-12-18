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
struct tnc_if_imv {scalar_t__ (* Initialize ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  imvID; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ TNC_Version ;
typedef  scalar_t__ TNC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TNC_IFIMV_VERSION_1 ; 
 scalar_t__ TNC_RESULT_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 

__attribute__((used)) static int tncs_imv_initialize(struct tnc_if_imv *imv)
{
	TNC_Result res;
	TNC_Version imv_ver;

	wpa_printf(MSG_DEBUG, "TNC: Calling TNC_IMV_Initialize for IMV '%s'",
		   imv->name);
	res = imv->Initialize(imv->imvID, TNC_IFIMV_VERSION_1,
			      TNC_IFIMV_VERSION_1, &imv_ver);
	wpa_printf(MSG_DEBUG, "TNC: TNC_IMV_Initialize: res=%lu imv_ver=%lu",
		   (unsigned long) res, (unsigned long) imv_ver);

	return res == TNC_RESULT_SUCCESS ? 0 : -1;
}