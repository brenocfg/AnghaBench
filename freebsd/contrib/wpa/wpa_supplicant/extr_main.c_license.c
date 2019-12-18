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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* wpa_supplicant_full_license1 ; 
 char* wpa_supplicant_full_license2 ; 
 char* wpa_supplicant_full_license3 ; 
 int /*<<< orphan*/  wpa_supplicant_full_license4 ; 
 int /*<<< orphan*/  wpa_supplicant_full_license5 ; 
 char* wpa_supplicant_version ; 

__attribute__((used)) static void license(void)
{
#ifndef CONFIG_NO_STDOUT_DEBUG
	printf("%s\n\n%s%s%s%s%s\n",
	       wpa_supplicant_version,
	       wpa_supplicant_full_license1,
	       wpa_supplicant_full_license2,
	       wpa_supplicant_full_license3,
	       wpa_supplicant_full_license4,
	       wpa_supplicant_full_license5);
#endif /* CONFIG_NO_STDOUT_DEBUG */
}