#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct sbuf {int dummy; } ;
struct config_value {void* value; } ;
struct config_entry {void* value; void* list; } ;
typedef  scalar_t__ pkg_conf_file_t ;
struct TYPE_10__ {int type; int main_only; void* value; void* list; scalar_t__ envset; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ CONFFILE_PKG ; 
 scalar_t__ CONFFILE_REPO ; 
 int CONFIG_SIZE ; 
#define  PKG_CONFIG_BOOL 129 
#define  PKG_CONFIG_LIST 128 
 int /*<<< orphan*/  STAILQ_INIT (void*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (void*,struct config_value*,int /*<<< orphan*/ ) ; 
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_BOOLEAN ; 
 scalar_t__ UCL_STRING ; 
 TYPE_8__* c ; 
 struct config_entry* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct config_entry*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_cpy (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char const) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdup (char*) ; 
 size_t strlen (char const*) ; 
 TYPE_1__* ucl_iterate_object (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (TYPE_1__ const*) ; 
 scalar_t__ ucl_object_toboolean (TYPE_1__ const*) ; 
 char* ucl_object_tostring (TYPE_1__ const*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
config_parse(const ucl_object_t *obj, pkg_conf_file_t conftype)
{
	struct sbuf *buf = sbuf_new_auto();
	const ucl_object_t *cur, *seq;
	ucl_object_iter_t it = NULL, itseq = NULL;
	struct config_entry *temp_config;
	struct config_value *cv;
	const char *key;
	int i;
	size_t j;

	/* Temporary config for configs that may be disabled. */
	temp_config = calloc(CONFIG_SIZE, sizeof(struct config_entry));

	while ((cur = ucl_iterate_object(obj, &it, true))) {
		key = ucl_object_key(cur);
		if (key == NULL)
			continue;
		sbuf_clear(buf);

		if (conftype == CONFFILE_PKG) {
			for (j = 0; j < strlen(key); ++j)
				sbuf_putc(buf, key[j]);
			sbuf_finish(buf);
		} else if (conftype == CONFFILE_REPO) {
			if (strcasecmp(key, "url") == 0)
				sbuf_cpy(buf, "PACKAGESITE");
			else if (strcasecmp(key, "mirror_type") == 0)
				sbuf_cpy(buf, "MIRROR_TYPE");
			else if (strcasecmp(key, "signature_type") == 0)
				sbuf_cpy(buf, "SIGNATURE_TYPE");
			else if (strcasecmp(key, "fingerprints") == 0)
				sbuf_cpy(buf, "FINGERPRINTS");
			else if (strcasecmp(key, "pubkey") == 0)
				sbuf_cpy(buf, "PUBKEY");
			else if (strcasecmp(key, "enabled") == 0) {
				if ((cur->type != UCL_BOOLEAN) ||
				    !ucl_object_toboolean(cur))
					goto cleanup;
			} else
				continue;
			sbuf_finish(buf);
		}

		for (i = 0; i < CONFIG_SIZE; i++) {
			if (strcmp(sbuf_data(buf), c[i].key) == 0)
				break;
		}

		/* Silently skip unknown keys to be future compatible. */
		if (i == CONFIG_SIZE)
			continue;

		/* env has priority over config file */
		if (c[i].envset)
			continue;

		/* Parse sequence value ["item1", "item2"] */
		switch (c[i].type) {
		case PKG_CONFIG_LIST:
			if (cur->type != UCL_ARRAY) {
				warnx("Skipping invalid array "
				    "value for %s.\n", c[i].key);
				continue;
			}
			temp_config[i].list =
			    malloc(sizeof(*temp_config[i].list));
			STAILQ_INIT(temp_config[i].list);

			while ((seq = ucl_iterate_object(cur, &itseq, true))) {
				if (seq->type != UCL_STRING)
					continue;
				cv = malloc(sizeof(struct config_value));
				cv->value =
				    strdup(ucl_object_tostring(seq));
				STAILQ_INSERT_TAIL(temp_config[i].list, cv,
				    next);
			}
			break;
		case PKG_CONFIG_BOOL:
			temp_config[i].value =
			    strdup(ucl_object_toboolean(cur) ? "yes" : "no");
			break;
		default:
			/* Normal string value. */
			temp_config[i].value = strdup(ucl_object_tostring(cur));
			break;
		}
	}

	/* Repo is enabled, copy over all settings from temp_config. */
	for (i = 0; i < CONFIG_SIZE; i++) {
		if (c[i].envset)
			continue;
		/* Prevent overriding ABI, ASSUME_ALWAYS_YES, etc. */
		if (conftype != CONFFILE_PKG && c[i].main_only == true)
			continue;
		switch (c[i].type) {
		case PKG_CONFIG_LIST:
			c[i].list = temp_config[i].list;
			break;
		default:
			c[i].value = temp_config[i].value;
			break;
		}
	}

cleanup:
	free(temp_config);
	sbuf_delete(buf);
}