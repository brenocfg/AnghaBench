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
typedef  int /*<<< orphan*/  TNC_IMCID ;
typedef  int /*<<< orphan*/  TNC_ConnectionID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static TNC_Result TNC_9048_UserMessage(TNC_IMCID imcID,
				       TNC_ConnectionID connectionID,
				       const char *message)
{
	wpa_printf(MSG_DEBUG, "TNC: TNC_9048_UserMessage(imcID=%lu "
		   "connectionID==%lu message='%s')",
		   imcID, connectionID, message);
	return TNC_RESULT_SUCCESS;
}