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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_SUBKEY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetSystemDirectory (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ Initialized ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  baseLen ; 
 scalar_t__ local_state_dir ; 
 scalar_t__ lwresd_confFile ; 
 scalar_t__ lwresd_defaultpidfile ; 
 scalar_t__ lwresd_resolvconfFile ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ namedBase ; 
 scalar_t__ ns_confFile ; 
 scalar_t__ ns_defaultpidfile ; 
 scalar_t__ rndc_confFile ; 
 scalar_t__ rndc_keyFile ; 
 scalar_t__ session_keyFile ; 
 int /*<<< orphan*/  strcat (scalar_t__,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 
 scalar_t__ sys_conf_dir ; 
 scalar_t__ systemDir ; 

void
isc_ntpaths_init() {
	HKEY hKey;
	BOOL keyFound = TRUE;

	memset(namedBase, 0, MAX_PATH);
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, BIND_SUBKEY, 0, KEY_READ, &hKey)
		!= ERROR_SUCCESS)
		keyFound = FALSE;

	if (keyFound == TRUE) {
		/* Get the named directory */
		if (RegQueryValueEx(hKey, "InstallDir", NULL, NULL,
			(LPBYTE)namedBase, &baseLen) != ERROR_SUCCESS)
			keyFound = FALSE;
		RegCloseKey(hKey);
	}

	GetSystemDirectory(systemDir, MAX_PATH);

	if (keyFound == FALSE)
		/* Use the System Directory as a default */
		strcpy(namedBase, systemDir);

	strcpy(ns_confFile, namedBase);
	strcat(ns_confFile, "\\etc\\named.conf");

	strcpy(lwresd_confFile, namedBase);
	strcat(lwresd_confFile, "\\etc\\lwresd.conf");

	strcpy(lwresd_resolvconfFile, systemDir);
	strcat(lwresd_resolvconfFile, "\\Drivers\\etc\\resolv.conf");

	strcpy(rndc_keyFile, namedBase);
	strcat(rndc_keyFile, "\\etc\\rndc.key");

	strcpy(session_keyFile, namedBase);
	strcat(session_keyFile, "\\etc\\session.key");

	strcpy(rndc_confFile, namedBase);
	strcat(rndc_confFile, "\\etc\\rndc.conf");
	strcpy(ns_defaultpidfile, namedBase);
	strcat(ns_defaultpidfile, "\\etc\\named.pid");

	strcpy(lwresd_defaultpidfile, namedBase);
	strcat(lwresd_defaultpidfile, "\\etc\\lwresd.pid");

	strcpy(local_state_dir, namedBase);
	strcat(local_state_dir, "\\bin");

	strcpy(sys_conf_dir, namedBase);
	strcat(sys_conf_dir, "\\etc");

	Initialized = TRUE;
}