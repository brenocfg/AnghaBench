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
struct eap_sim_db_data {int sock; void (* get_complete_cb ) (void*,void*) ;unsigned int eap_sim_db_timeout; struct eap_sim_db_data* fname; int /*<<< orphan*/ * sqlite_db; void* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * db_open (char*) ; 
 int /*<<< orphan*/  eap_sim_db_close_socket (struct eap_sim_db_data*) ; 
 scalar_t__ eap_sim_db_open_socket (struct eap_sim_db_data*) ; 
 int /*<<< orphan*/  os_free (struct eap_sim_db_data*) ; 
 struct eap_sim_db_data* os_strdup (char const*) ; 
 scalar_t__ os_strncmp (struct eap_sim_db_data*,char*,int) ; 
 char* os_strstr (struct eap_sim_db_data*,char*) ; 
 struct eap_sim_db_data* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct eap_sim_db_data *
eap_sim_db_init(const char *config, unsigned int db_timeout,
		void (*get_complete_cb)(void *ctx, void *session_ctx),
		void *ctx)
{
	struct eap_sim_db_data *data;
	char *pos;

	data = os_zalloc(sizeof(*data));
	if (data == NULL)
		return NULL;

	data->sock = -1;
	data->get_complete_cb = get_complete_cb;
	data->ctx = ctx;
	data->eap_sim_db_timeout = db_timeout;
	data->fname = os_strdup(config);
	if (data->fname == NULL)
		goto fail;
	pos = os_strstr(data->fname, " db=");
	if (pos) {
		*pos = '\0';
#ifdef CONFIG_SQLITE
		pos += 4;
		data->sqlite_db = db_open(pos);
		if (data->sqlite_db == NULL)
			goto fail;
#endif /* CONFIG_SQLITE */
	}

	if (os_strncmp(data->fname, "unix:", 5) == 0) {
		if (eap_sim_db_open_socket(data)) {
			wpa_printf(MSG_DEBUG, "EAP-SIM DB: External database "
				   "connection not available - will retry "
				   "later");
		}
	}

	return data;

fail:
	eap_sim_db_close_socket(data);
	os_free(data->fname);
	os_free(data);
	return NULL;
}