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
struct align {int position; unsigned int width; } ;
struct TYPE_3__ {struct align align; } ;
struct used_atom {TYPE_1__ u; } ;
struct string_list {int nr; TYPE_2__* items; } ;
struct strbuf {int dummy; } ;
struct ref_format {int dummy; } ;
struct TYPE_4__ {char* string; } ;

/* Variables and functions */
 int ALIGN_LEFT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int parse_align_position (char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,char const*) ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_split (struct string_list*,char const*,char,int) ; 
 scalar_t__ strtoul_ui (char const*,int,unsigned int*) ; 

__attribute__((used)) static int align_atom_parser(const struct ref_format *format, struct used_atom *atom,
			     const char *arg, struct strbuf *err)
{
	struct align *align = &atom->u.align;
	struct string_list params = STRING_LIST_INIT_DUP;
	int i;
	unsigned int width = ~0U;

	if (!arg)
		return strbuf_addf_ret(err, -1, _("expected format: %%(align:<width>,<position>)"));

	align->position = ALIGN_LEFT;

	string_list_split(&params, arg, ',', -1);
	for (i = 0; i < params.nr; i++) {
		const char *s = params.items[i].string;
		int position;

		if (skip_prefix(s, "position=", &s)) {
			position = parse_align_position(s);
			if (position < 0) {
				strbuf_addf(err, _("unrecognized position:%s"), s);
				string_list_clear(&params, 0);
				return -1;
			}
			align->position = position;
		} else if (skip_prefix(s, "width=", &s)) {
			if (strtoul_ui(s, 10, &width)) {
				strbuf_addf(err, _("unrecognized width:%s"), s);
				string_list_clear(&params, 0);
				return -1;
			}
		} else if (!strtoul_ui(s, 10, &width))
			;
		else if ((position = parse_align_position(s)) >= 0)
			align->position = position;
		else {
			strbuf_addf(err, _("unrecognized %%(align) argument: %s"), s);
			string_list_clear(&params, 0);
			return -1;
		}
	}

	if (width == ~0U) {
		string_list_clear(&params, 0);
		return strbuf_addf_ret(err, -1, _("positive width expected with the %%(align) atom"));
	}
	align->width = width;
	string_list_clear(&params, 0);
	return 0;
}