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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_submodule_name (int /*<<< orphan*/ ) ; 
 int parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int name_and_item_from_var(const char *var, struct strbuf *name,
				  struct strbuf *item)
{
	const char *subsection, *key;
	int subsection_len, parse;
	parse = parse_config_key(var, "submodule", &subsection,
			&subsection_len, &key);
	if (parse < 0 || !subsection)
		return 0;

	strbuf_add(name, subsection, subsection_len);
	if (check_submodule_name(name->buf) < 0) {
		warning(_("ignoring suspicious submodule name: %s"), name->buf);
		strbuf_release(name);
		return 0;
	}

	strbuf_addstr(item, key);

	return 1;
}