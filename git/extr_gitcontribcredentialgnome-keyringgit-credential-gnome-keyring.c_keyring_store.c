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
struct credential {int /*<<< orphan*/  password; int /*<<< orphan*/  port; int /*<<< orphan*/  protocol; scalar_t__ host; int /*<<< orphan*/  username; scalar_t__ path; } ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  scalar_t__ GnomeKeyringResult ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  GNOME_KEYRING_DEFAULT ; 
 scalar_t__ GNOME_KEYRING_RESULT_CANCELLED ; 
 scalar_t__ GNOME_KEYRING_RESULT_OK ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  gnome_keyring_result_to_message (scalar_t__) ; 
 scalar_t__ gnome_keyring_set_network_password_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* keyring_object (struct credential*) ; 

__attribute__((used)) static int keyring_store(struct credential *c)
{
	guint32 item_id;
	char *object = NULL;
	GnomeKeyringResult result;

	/*
	 * Sanity check that what we are storing is actually sensible.
	 * In particular, we can't make a URL without a protocol field.
	 * Without either a host or pathname (depending on the scheme),
	 * we have no primary key. And without a username and password,
	 * we are not actually storing a credential.
	 */
	if (!c->protocol || !(c->host || c->path) ||
	    !c->username || !c->password)
		return EXIT_FAILURE;

	object = keyring_object(c);

	result = gnome_keyring_set_network_password_sync(
				GNOME_KEYRING_DEFAULT,
				c->username,
				NULL /* domain */,
				c->host,
				object,
				c->protocol,
				NULL /* authtype */,
				c->port,
				c->password,
				&item_id);

	g_free(object);

	if (result != GNOME_KEYRING_RESULT_OK &&
	    result != GNOME_KEYRING_RESULT_CANCELLED) {
		g_critical("%s", gnome_keyring_result_to_message(result));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}