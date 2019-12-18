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
struct TYPE_2__ {int /*<<< orphan*/  color; } ;
struct used_atom {TYPE_1__ u; } ;
struct strbuf {int dummy; } ;
struct ref_format {int /*<<< orphan*/  use_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ color_parse (char const*,int /*<<< orphan*/ ) ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  want_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int color_atom_parser(const struct ref_format *format, struct used_atom *atom,
			     const char *color_value, struct strbuf *err)
{
	if (!color_value)
		return strbuf_addf_ret(err, -1, _("expected format: %%(color:<color>)"));
	if (color_parse(color_value, atom->u.color) < 0)
		return strbuf_addf_ret(err, -1, _("unrecognized color: %%(color:%s)"),
				       color_value);
	/*
	 * We check this after we've parsed the color, which lets us complain
	 * about syntactically bogus color names even if they won't be used.
	 */
	if (!want_color(format->use_color))
		color_parse("", atom->u.color);
	return 0;
}