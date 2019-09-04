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
struct TYPE_2__ {int /*<<< orphan*/  refname; } ;
struct used_atom {int /*<<< orphan*/  name; TYPE_1__ u; } ;
struct strbuf {int dummy; } ;
struct ref_format {int dummy; } ;

/* Variables and functions */
 int refname_atom_parser_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct strbuf*) ; 

__attribute__((used)) static int refname_atom_parser(const struct ref_format *format, struct used_atom *atom,
			       const char *arg, struct strbuf *err)
{
	return refname_atom_parser_internal(&atom->u.refname, arg, atom->name, err);
}