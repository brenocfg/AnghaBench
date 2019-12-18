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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AID_WIFI ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ chmod (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lchown (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int android_update_permission(const char *path, mode_t mode)
{
#ifdef ANDROID
	/* we need to change file/folder permission for Android */

	if (!path) {
		wpa_printf(MSG_ERROR, "file path null");
		return -1;
	}

	/* Allow processes running with Group ID as AID_WIFI,
	 * to read files from SP, SP/<fqdn>, Cert and osu-info directories */
	if (lchown(path, -1, AID_WIFI)) {
		wpa_printf(MSG_INFO, "CTRL: Could not lchown directory: %s",
			   strerror(errno));
		return -1;
	}

	if (chmod(path, mode) < 0) {
		wpa_printf(MSG_INFO, "CTRL: Could not chmod directory: %s",
			   strerror(errno));
		return -1;
	}
#endif  /* ANDROID */

	return 0;
}