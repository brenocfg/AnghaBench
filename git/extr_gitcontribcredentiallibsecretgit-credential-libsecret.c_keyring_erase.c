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
struct credential {int /*<<< orphan*/  username; int /*<<< orphan*/  path; int /*<<< orphan*/  host; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SECRET_SCHEMA_COMPAT_NETWORK ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_attr_list (struct credential*) ; 
 int /*<<< orphan*/  secret_password_clearv_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static int keyring_erase(struct credential *c)
{
	GHashTable *attributes = NULL;
	GError *error = NULL;

	/*
	 * Sanity check that we actually have something to match
	 * against. The input we get is a restrictive pattern,
	 * so technically a blank credential means "erase everything".
	 * But it is too easy to accidentally send this, since it is equivalent
	 * to empty input. So explicitly disallow it, and require that the
	 * pattern have some actual content to match.
	 */
	if (!c->protocol && !c->host && !c->path && !c->username)
		return EXIT_FAILURE;

	attributes = make_attr_list(c);
	secret_password_clearv_sync(SECRET_SCHEMA_COMPAT_NETWORK,
				    attributes,
				    NULL,
				    &error);
	g_hash_table_unref(attributes);

	if (error != NULL) {
		g_critical("erase failed: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}