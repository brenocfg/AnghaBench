#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct credential {int /*<<< orphan*/  password; int /*<<< orphan*/  username; scalar_t__ path; scalar_t__ host; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SECRET_SCHEMA_COMPAT_NETWORK ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_hash_table_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_attr_list (struct credential*) ; 
 char* make_label (struct credential*) ; 
 int /*<<< orphan*/  secret_password_storev_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static int keyring_store(struct credential *c)
{
	char *label = NULL;
	GHashTable *attributes = NULL;
	GError *error = NULL;

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

	label = make_label(c);
	attributes = make_attr_list(c);
	secret_password_storev_sync(SECRET_SCHEMA_COMPAT_NETWORK,
				    attributes,
				    NULL,
				    label,
				    c->password,
				    NULL,
				    &error);
	g_free(label);
	g_hash_table_unref(attributes);

	if (error != NULL) {
		g_critical("store failed: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}