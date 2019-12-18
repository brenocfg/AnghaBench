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
typedef  int /*<<< orphan*/  SecKeychainItemRef ;

/* Variables and functions */
 int /*<<< orphan*/  KEYCHAIN_ARGS ; 
 scalar_t__ SecKeychainFindInternetPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SecKeychainItemDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  protocol ; 

__attribute__((used)) static void delete_internet_password(void)
{
	SecKeychainItemRef item;

	/*
	 * Require at least a protocol and host for removal, which is what git
	 * will give us; if you want to do something more fancy, use the
	 * Keychain manager.
	 */
	if (!protocol || !host)
		return;

	if (SecKeychainFindInternetPassword(KEYCHAIN_ARGS, 0, NULL, &item))
		return;

	SecKeychainItemDelete(item);
}