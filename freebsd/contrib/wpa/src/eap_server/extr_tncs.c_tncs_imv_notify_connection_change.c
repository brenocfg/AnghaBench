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
struct tnc_if_imv {scalar_t__ (* NotifyConnectionChange ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  imvID; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ TNC_Result ;
typedef  scalar_t__ TNC_ConnectionState ;
typedef  int /*<<< orphan*/  TNC_ConnectionID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ TNC_RESULT_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 

__attribute__((used)) static int tncs_imv_notify_connection_change(struct tnc_if_imv *imv,
					     TNC_ConnectionID conn,
					     TNC_ConnectionState state)
{
	TNC_Result res;

	if (imv->NotifyConnectionChange == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "TNC: Calling TNC_IMV_NotifyConnectionChange(%d)"
		   " for IMV '%s'", (int) state, imv->name);
	res = imv->NotifyConnectionChange(imv->imvID, conn, state);
	wpa_printf(MSG_DEBUG, "TNC: TNC_IMC_NotifyConnectionChange: %lu",
		   (unsigned long) res);

	return res == TNC_RESULT_SUCCESS ? 0 : -1;
}