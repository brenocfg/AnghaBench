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
 int /*<<< orphan*/  KEYCHAIN_ARGS ; 
 int /*<<< orphan*/  KEYCHAIN_ITEM (int /*<<< orphan*/ ) ; 
 scalar_t__ SecKeychainAddInternetPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  password ; 
 int /*<<< orphan*/  protocol ; 
 int /*<<< orphan*/  username ; 

__attribute__((used)) static void add_internet_password(void)
{
	/* Only store complete credentials */
	if (!protocol || !host || !username || !password)
		return;

	if (SecKeychainAddInternetPassword(
	      KEYCHAIN_ARGS,
	      KEYCHAIN_ITEM(password),
	      NULL))
		return;
}