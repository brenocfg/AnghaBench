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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct credential {int quit; void* path; void* host; void* protocol; void* password; void* username; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  credential_from_url (struct credential*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  git_config_bool (char*,char*) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 
 void* xstrdup (char*) ; 

int credential_read(struct credential *c, FILE *fp)
{
	struct strbuf line = STRBUF_INIT;

	while (strbuf_getline_lf(&line, fp) != EOF) {
		char *key = line.buf;
		char *value = strchr(key, '=');

		if (!line.len)
			break;

		if (!value) {
			warning("invalid credential line: %s", key);
			strbuf_release(&line);
			return -1;
		}
		*value++ = '\0';

		if (!strcmp(key, "username")) {
			free(c->username);
			c->username = xstrdup(value);
		} else if (!strcmp(key, "password")) {
			free(c->password);
			c->password = xstrdup(value);
		} else if (!strcmp(key, "protocol")) {
			free(c->protocol);
			c->protocol = xstrdup(value);
		} else if (!strcmp(key, "host")) {
			free(c->host);
			c->host = xstrdup(value);
		} else if (!strcmp(key, "path")) {
			free(c->path);
			c->path = xstrdup(value);
		} else if (!strcmp(key, "url")) {
			credential_from_url(c, value);
		} else if (!strcmp(key, "quit")) {
			c->quit = !!git_config_bool("quit", value);
		}
		/*
		 * Ignore other lines; we don't know what they mean, but
		 * this future-proofs us when later versions of git do
		 * learn new lines, and the helpers are updated to match.
		 */
	}

	strbuf_release(&line);
	return 0;
}