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
struct tnc_if_imc {unsigned long name; scalar_t__ (* ProvideBindFunction ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  imcID; } ;
typedef  scalar_t__ TNC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ TNC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  TNC_TNCC_BindFunction ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int tncc_imc_provide_bind_function(struct tnc_if_imc *imc)
{
	TNC_Result res;

	wpa_printf(MSG_DEBUG, "TNC: Calling TNC_IMC_ProvideBindFunction for "
		   "IMC '%s'", imc->name);
	res = imc->ProvideBindFunction(imc->imcID, TNC_TNCC_BindFunction);
	wpa_printf(MSG_DEBUG, "TNC: TNC_IMC_ProvideBindFunction: res=%lu",
		   (unsigned long) res);

	return res == TNC_RESULT_SUCCESS ? 0 : -1;
}