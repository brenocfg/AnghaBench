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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct notes_cache {int /*<<< orphan*/  tree; int /*<<< orphan*/  validity; } ;

/* Variables and functions */
 int NOTES_INIT_EMPTY ; 
 int NOTES_INIT_WRITABLE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  combine_notes_overwrite ; 
 int /*<<< orphan*/  init_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct notes_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notes_cache_match_validity (struct repository*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void notes_cache_init(struct repository *r, struct notes_cache *c,
		      const char *name, const char *validity)
{
	struct strbuf ref = STRBUF_INIT;
	int flags = NOTES_INIT_WRITABLE;

	memset(c, 0, sizeof(*c));
	c->validity = xstrdup(validity);

	strbuf_addf(&ref, "refs/notes/%s", name);
	if (!notes_cache_match_validity(r, ref.buf, validity))
		flags |= NOTES_INIT_EMPTY;
	init_notes(&c->tree, ref.buf, combine_notes_overwrite, flags);
	strbuf_release(&ref);
}