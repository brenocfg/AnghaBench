#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {char* username; char* password; } ;
struct credential_cache_entry {TYPE_1__ item; } ;
struct credential {int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct credential CREDENTIAL_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  cache_credential (struct credential*,int) ; 
 int /*<<< orphan*/  credential_clear (struct credential*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 struct credential_cache_entry* lookup_credential (struct credential*) ; 
 scalar_t__ read_request (int /*<<< orphan*/ *,struct credential*,struct strbuf*,int*) ; 
 int /*<<< orphan*/  remove_credential (struct credential*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static void serve_one_client(FILE *in, FILE *out)
{
	struct credential c = CREDENTIAL_INIT;
	struct strbuf action = STRBUF_INIT;
	int timeout = -1;

	if (read_request(in, &c, &action, &timeout) < 0)
		/* ignore error */ ;
	else if (!strcmp(action.buf, "get")) {
		struct credential_cache_entry *e = lookup_credential(&c);
		if (e) {
			fprintf(out, "username=%s\n", e->item.username);
			fprintf(out, "password=%s\n", e->item.password);
		}
	}
	else if (!strcmp(action.buf, "exit")) {
		/*
		 * It's important that we clean up our socket first, and then
		 * signal the client only once we have finished the cleanup.
		 * Calling exit() directly does this, because we clean up in
		 * our atexit() handler, and then signal the client when our
		 * process actually ends, which closes the socket and gives
		 * them EOF.
		 */
		exit(0);
	}
	else if (!strcmp(action.buf, "erase"))
		remove_credential(&c);
	else if (!strcmp(action.buf, "store")) {
		if (timeout < 0)
			warning("cache client didn't specify a timeout");
		else if (!c.username || !c.password)
			warning("cache client gave us a partial credential");
		else {
			remove_credential(&c);
			cache_credential(&c, timeout);
		}
	}
	else
		warning("cache client sent unknown action: %s", action.buf);

	credential_clear(&c);
	strbuf_release(&action);
}