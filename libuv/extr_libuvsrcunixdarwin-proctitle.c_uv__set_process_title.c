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
typedef  int /*<<< orphan*/  namebuf ;
typedef  int /*<<< orphan*/  CFTypeRef ;

/* Variables and functions */
 int /*<<< orphan*/  S (char const*) ; 
 int /*<<< orphan*/ * core_foundation_handle ; 
 int /*<<< orphan*/ * display_name_key ; 
 int /*<<< orphan*/  dynamic_pthread_setname_np (char*) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  pCFBundleGetInfoDictionary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCFBundleGetMainBundle () ; 
 int /*<<< orphan*/  pLSApplicationCheckIn (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pLSGetCurrentApplicationASN () ; 
 int /*<<< orphan*/  pLSSetApplicationInformationItem (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pLSSetApplicationLaunchServicesServerConnectionStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pSetApplicationIsDaemon (int) ; 
 int /*<<< orphan*/  uv__strscpy (char*,char const*,int) ; 

void uv__set_process_title(const char* title) {
#if !TARGET_OS_IPHONE
  if (core_foundation_handle != NULL && pSetApplicationIsDaemon(1) != noErr) {
    CFTypeRef asn;
    pLSSetApplicationLaunchServicesServerConnectionStatus(0, NULL);
    pLSApplicationCheckIn(/* Magic value */ -2,
                          pCFBundleGetInfoDictionary(pCFBundleGetMainBundle()));
    asn = pLSGetCurrentApplicationASN();
    pLSSetApplicationInformationItem(/* Magic value */ -2, asn,
                                     *display_name_key, S(title), NULL);
  }
#endif  /* !TARGET_OS_IPHONE */

  if (dynamic_pthread_setname_np != NULL) {
    char namebuf[64];  /* MAXTHREADNAMESIZE */
    uv__strscpy(namebuf, title, sizeof(namebuf));
    dynamic_pthread_setname_np(namebuf);
  }
}