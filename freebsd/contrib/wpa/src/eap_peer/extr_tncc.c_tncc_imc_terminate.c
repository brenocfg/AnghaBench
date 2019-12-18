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
struct tnc_if_imc {scalar_t__ (* Terminate ) (int /*<<< orphan*/ ) ;unsigned long name; int /*<<< orphan*/  imcID; } ;
typedef  scalar_t__ TNC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ TNC_RESULT_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int tncc_imc_terminate(struct tnc_if_imc *imc)
{
	TNC_Result res;

	if (imc->Terminate == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "TNC: Calling TNC_IMC_Terminate for IMC '%s'",
		   imc->name);
	res = imc->Terminate(imc->imcID);
	wpa_printf(MSG_DEBUG, "TNC: TNC_IMC_Terminate: %lu",
		   (unsigned long) res);

	return res == TNC_RESULT_SUCCESS ? 0 : -1;
}