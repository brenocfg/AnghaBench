#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct repository {TYPE_2__* objects; } ;
struct TYPE_4__ {TYPE_1__* odb; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  link_alt_odb_entry (struct repository*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 char* parse_alt_odb_entry (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_normalize_path (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void link_alt_odb_entries(struct repository *r, const char *alt,
				 int sep, const char *relative_base, int depth)
{
	struct strbuf objdirbuf = STRBUF_INIT;
	struct strbuf entry = STRBUF_INIT;

	if (!alt || !*alt)
		return;

	if (depth > 5) {
		error(_("%s: ignoring alternate object stores, nesting too deep"),
				relative_base);
		return;
	}

	strbuf_add_absolute_path(&objdirbuf, r->objects->odb->path);
	if (strbuf_normalize_path(&objdirbuf) < 0)
		die(_("unable to normalize object directory: %s"),
		    objdirbuf.buf);

	while (*alt) {
		alt = parse_alt_odb_entry(alt, sep, &entry);
		if (!entry.len)
			continue;
		link_alt_odb_entry(r, entry.buf,
				   relative_base, depth, objdirbuf.buf);
	}
	strbuf_release(&entry);
	strbuf_release(&objdirbuf);
}