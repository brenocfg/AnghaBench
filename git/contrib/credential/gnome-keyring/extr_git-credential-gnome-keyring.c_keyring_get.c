#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct credential {int /*<<< orphan*/  username; int /*<<< orphan*/  password; int /*<<< orphan*/  port; int /*<<< orphan*/  protocol; scalar_t__ host; scalar_t__ path; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  user; int /*<<< orphan*/  password; } ;
typedef  scalar_t__ GnomeKeyringResult ;
typedef  TYPE_1__ GnomeKeyringNetworkPasswordData ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ GNOME_KEYRING_RESULT_CANCELLED ; 
 scalar_t__ GNOME_KEYRING_RESULT_NO_MATCH ; 
 scalar_t__ GNOME_KEYRING_RESULT_OK ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ gnome_keyring_find_network_password_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  gnome_keyring_memory_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnome_keyring_memory_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnome_keyring_network_password_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  gnome_keyring_result_to_message (scalar_t__) ; 
 char* keyring_object (struct credential*) ; 

__attribute__((used)) static int keyring_get(struct credential *c)
{
	char *object = NULL;
	GList *entries;
	GnomeKeyringNetworkPasswordData *password_data;
	GnomeKeyringResult result;

	if (!c->protocol || !(c->host || c->path))
		return EXIT_FAILURE;

	object = keyring_object(c);

	result = gnome_keyring_find_network_password_sync(
				c->username,
				NULL /* domain */,
				c->host,
				object,
				c->protocol,
				NULL /* authtype */,
				c->port,
				&entries);

	g_free(object);

	if (result == GNOME_KEYRING_RESULT_NO_MATCH)
		return EXIT_SUCCESS;

	if (result == GNOME_KEYRING_RESULT_CANCELLED)
		return EXIT_SUCCESS;

	if (result != GNOME_KEYRING_RESULT_OK) {
		g_critical("%s", gnome_keyring_result_to_message(result));
		return EXIT_FAILURE;
	}

	/* pick the first one from the list */
	password_data = (GnomeKeyringNetworkPasswordData *)entries->data;

	gnome_keyring_memory_free(c->password);
	c->password = gnome_keyring_memory_strdup(password_data->password);

	if (!c->username)
		c->username = g_strdup(password_data->user);

	gnome_keyring_network_password_list_free(entries);

	return EXIT_SUCCESS;
}