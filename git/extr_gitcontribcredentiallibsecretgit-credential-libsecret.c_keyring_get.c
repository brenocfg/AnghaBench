#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct credential {void* password; void* username; scalar_t__ path; scalar_t__ host; int /*<<< orphan*/  protocol; } ;
struct TYPE_9__ {int /*<<< orphan*/  message; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  SecretValue ;
typedef  int /*<<< orphan*/  SecretService ;
typedef  int /*<<< orphan*/  SecretItem ;
typedef  TYPE_1__ GList ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_2__ GError ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SECRET_SCHEMA_COMPAT_NETWORK ; 
 int SECRET_SEARCH_LOAD_SECRETS ; 
 int SECRET_SEARCH_UNLOCK ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_free (void*) ; 
 char* g_hash_table_lookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_hash_table_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref ; 
 void* g_strdup (char const*) ; 
 int /*<<< orphan*/ * make_attr_list (struct credential*) ; 
 int /*<<< orphan*/ * secret_item_get_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * secret_item_get_secret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * secret_service_get_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**) ; 
 TYPE_1__* secret_service_search_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_2__**) ; 
 char* secret_value_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secret_value_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int keyring_get(struct credential *c)
{
	SecretService *service = NULL;
	GHashTable *attributes = NULL;
	GError *error = NULL;
	GList *items = NULL;

	if (!c->protocol || !(c->host || c->path))
		return EXIT_FAILURE;

	service = secret_service_get_sync(0, NULL, &error);
	if (error != NULL) {
		g_critical("could not connect to Secret Service: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	attributes = make_attr_list(c);
	items = secret_service_search_sync(service,
					   SECRET_SCHEMA_COMPAT_NETWORK,
					   attributes,
					   SECRET_SEARCH_LOAD_SECRETS | SECRET_SEARCH_UNLOCK,
					   NULL,
					   &error);
	g_hash_table_unref(attributes);
	if (error != NULL) {
		g_critical("lookup failed: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	if (items != NULL) {
		SecretItem *item;
		SecretValue *secret;
		const char *s;

		item = items->data;
		secret = secret_item_get_secret(item);
		attributes = secret_item_get_attributes(item);

		s = g_hash_table_lookup(attributes, "user");
		if (s) {
			g_free(c->username);
			c->username = g_strdup(s);
		}

		s = secret_value_get_text(secret);
		if (s) {
			g_free(c->password);
			c->password = g_strdup(s);
		}

		g_hash_table_unref(attributes);
		secret_value_unref(secret);
		g_list_free_full(items, g_object_unref);
	}

	return EXIT_SUCCESS;
}