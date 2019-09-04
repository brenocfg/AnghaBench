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
struct strbuf {int dummy; } ;
struct ref {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 char* resolve_ref_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *guess_ref(const char *name, struct ref *peer)
{
	struct strbuf buf = STRBUF_INIT;

	const char *r = resolve_ref_unsafe(peer->name, RESOLVE_REF_READING,
					   NULL, NULL);
	if (!r)
		return NULL;

	if (starts_with(r, "refs/heads/")) {
		strbuf_addstr(&buf, "refs/heads/");
	} else if (starts_with(r, "refs/tags/")) {
		strbuf_addstr(&buf, "refs/tags/");
	} else {
		return NULL;
	}

	strbuf_addstr(&buf, name);
	return strbuf_detach(&buf, NULL);
}