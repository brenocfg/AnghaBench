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
struct tnc_if_imc {int /*<<< orphan*/ * path; int /*<<< orphan*/  name; int /*<<< orphan*/ * dlhandle; } ;
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 void* LoadLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlerror () ; 
 int /*<<< orphan*/ * dlopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ tncc_imc_initialize (struct tnc_if_imc*) ; 
 scalar_t__ tncc_imc_provide_bind_function (struct tnc_if_imc*) ; 
 scalar_t__ tncc_imc_resolve_funcs (struct tnc_if_imc*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpa_strdup_tchar (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tncc_load_imc(struct tnc_if_imc *imc)
{
	if (imc->path == NULL) {
		wpa_printf(MSG_DEBUG, "TNC: No IMC configured");
		return -1;
	}

	wpa_printf(MSG_DEBUG, "TNC: Opening IMC: %s (%s)",
		   imc->name, imc->path);
#ifdef CONFIG_NATIVE_WINDOWS
#ifdef UNICODE
	{
		TCHAR *lib = wpa_strdup_tchar(imc->path);
		if (lib == NULL)
			return -1;
		imc->dlhandle = LoadLibrary(lib);
		os_free(lib);
	}
#else /* UNICODE */
	imc->dlhandle = LoadLibrary(imc->path);
#endif /* UNICODE */
	if (imc->dlhandle == NULL) {
		wpa_printf(MSG_ERROR, "TNC: Failed to open IMC '%s' (%s): %d",
			   imc->name, imc->path, (int) GetLastError());
		return -1;
	}
#else /* CONFIG_NATIVE_WINDOWS */
	imc->dlhandle = dlopen(imc->path, RTLD_LAZY);
	if (imc->dlhandle == NULL) {
		wpa_printf(MSG_ERROR, "TNC: Failed to open IMC '%s' (%s): %s",
			   imc->name, imc->path, dlerror());
		return -1;
	}
#endif /* CONFIG_NATIVE_WINDOWS */

	if (tncc_imc_resolve_funcs(imc) < 0) {
		wpa_printf(MSG_ERROR, "TNC: Failed to resolve IMC functions");
		return -1;
	}

	if (tncc_imc_initialize(imc) < 0 ||
	    tncc_imc_provide_bind_function(imc) < 0) {
		wpa_printf(MSG_ERROR, "TNC: Failed to initialize IMC");
		return -1;
	}

	return 0;
}