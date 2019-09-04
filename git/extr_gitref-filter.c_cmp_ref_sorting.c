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
struct ref_sorting {size_t atom; scalar_t__ reverse; scalar_t__ version; scalar_t__ ignore_case; } ;
struct ref_array_item {char const* refname; } ;
struct atom_value {char const* s; scalar_t__ value; } ;
typedef  scalar_t__ cmp_type ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ FIELD_STR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ref_atom_value (struct ref_array_item*,size_t,struct atom_value**,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strcasecmp (char const*,char const*) ; 
 int strcmp (char const*,char const*) ; 
 TYPE_1__* used_atom ; 
 int versioncmp (char const*,char const*) ; 

__attribute__((used)) static int cmp_ref_sorting(struct ref_sorting *s, struct ref_array_item *a, struct ref_array_item *b)
{
	struct atom_value *va, *vb;
	int cmp;
	cmp_type cmp_type = used_atom[s->atom].type;
	int (*cmp_fn)(const char *, const char *);
	struct strbuf err = STRBUF_INIT;

	if (get_ref_atom_value(a, s->atom, &va, &err))
		die("%s", err.buf);
	if (get_ref_atom_value(b, s->atom, &vb, &err))
		die("%s", err.buf);
	strbuf_release(&err);
	cmp_fn = s->ignore_case ? strcasecmp : strcmp;
	if (s->version)
		cmp = versioncmp(va->s, vb->s);
	else if (cmp_type == FIELD_STR)
		cmp = cmp_fn(va->s, vb->s);
	else {
		if (va->value < vb->value)
			cmp = -1;
		else if (va->value == vb->value)
			cmp = cmp_fn(a->refname, b->refname);
		else
			cmp = 1;
	}

	return (s->reverse) ? -cmp : cmp;
}