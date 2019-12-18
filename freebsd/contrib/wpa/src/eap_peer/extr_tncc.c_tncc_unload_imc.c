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
struct tnc_if_imc {size_t imcID; int /*<<< orphan*/  imc_send; int /*<<< orphan*/  supported_types; int /*<<< orphan*/  path; int /*<<< orphan*/  name; scalar_t__ dlhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  dlclose (scalar_t__) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** tnc_imc ; 
 int /*<<< orphan*/  tncc_imc_terminate (struct tnc_if_imc*) ; 

__attribute__((used)) static void tncc_unload_imc(struct tnc_if_imc *imc)
{
	tncc_imc_terminate(imc);
	tnc_imc[imc->imcID] = NULL;

	if (imc->dlhandle) {
#ifdef CONFIG_NATIVE_WINDOWS
		FreeLibrary(imc->dlhandle);
#else /* CONFIG_NATIVE_WINDOWS */
		dlclose(imc->dlhandle);
#endif /* CONFIG_NATIVE_WINDOWS */
	}
	os_free(imc->name);
	os_free(imc->path);
	os_free(imc->supported_types);
	os_free(imc->imc_send);
}