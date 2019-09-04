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
struct credential {char* password; void* username; void* path; int /*<<< orphan*/  port; void* host; void* protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (void*) ; 
 void* g_strdup (char*) ; 
 int /*<<< orphan*/  g_warning (char*,char*) ; 
 char* gnome_keyring_memory_alloc (int) ; 
 int /*<<< orphan*/  gnome_keyring_memory_free (char*) ; 
 char* gnome_keyring_memory_strdup (char*) ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (void*,char) ; 

__attribute__((used)) static int credential_read(struct credential *c)
{
	char *buf;
	size_t line_len;
	char *key;
	char *value;

	key = buf = gnome_keyring_memory_alloc(1024);

	while (fgets(buf, 1024, stdin)) {
		line_len = strlen(buf);

		if (line_len && buf[line_len-1] == '\n')
			buf[--line_len] = '\0';

		if (!line_len)
			break;

		value = strchr(buf, '=');
		if (!value) {
			g_warning("invalid credential line: %s", key);
			gnome_keyring_memory_free(buf);
			return -1;
		}
		*value++ = '\0';

		if (!strcmp(key, "protocol")) {
			g_free(c->protocol);
			c->protocol = g_strdup(value);
		} else if (!strcmp(key, "host")) {
			g_free(c->host);
			c->host = g_strdup(value);
			value = strrchr(c->host, ':');
			if (value) {
				*value++ = '\0';
				c->port = atoi(value);
			}
		} else if (!strcmp(key, "path")) {
			g_free(c->path);
			c->path = g_strdup(value);
		} else if (!strcmp(key, "username")) {
			g_free(c->username);
			c->username = g_strdup(value);
		} else if (!strcmp(key, "password")) {
			gnome_keyring_memory_free(c->password);
			c->password = gnome_keyring_memory_strdup(value);
			while (*value)
				*value++ = '\0';
		}
		/*
		 * Ignore other lines; we don't know what they mean, but
		 * this future-proofs us when later versions of git do
		 * learn new lines, and the helpers are updated to match.
		 */
	}

	gnome_keyring_memory_free(buf);

	return 0;
}