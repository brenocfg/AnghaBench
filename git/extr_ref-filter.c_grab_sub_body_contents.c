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
struct TYPE_3__ {scalar_t__ option; int /*<<< orphan*/  trailer_opts; int /*<<< orphan*/  nlines; } ;
struct TYPE_4__ {TYPE_1__ contents; } ;
struct used_atom {char* name; TYPE_2__ u; } ;
struct strbuf {int dummy; } ;
struct atom_value {void* s; } ;

/* Variables and functions */
 scalar_t__ C_BARE ; 
 scalar_t__ C_BODY ; 
 scalar_t__ C_BODY_DEP ; 
 scalar_t__ C_LINES ; 
 scalar_t__ C_SIG ; 
 scalar_t__ C_SUB ; 
 scalar_t__ C_TRAILERS ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  append_lines (struct strbuf*,char const*,int,int /*<<< orphan*/ ) ; 
 void* copy_subject (char const*,unsigned long) ; 
 int /*<<< orphan*/  find_subpos (void*,char const**,unsigned long*,char const**,unsigned long*,unsigned long*,char const**,unsigned long*) ; 
 int /*<<< orphan*/  format_trailers_from_commit (struct strbuf*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 struct used_atom* used_atom ; 
 int used_atom_cnt ; 
 void* xmemdupz (char const*,unsigned long) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static void grab_sub_body_contents(struct atom_value *val, int deref, void *buf)
{
	int i;
	const char *subpos = NULL, *bodypos = NULL, *sigpos = NULL;
	unsigned long sublen = 0, bodylen = 0, nonsiglen = 0, siglen = 0;

	for (i = 0; i < used_atom_cnt; i++) {
		struct used_atom *atom = &used_atom[i];
		const char *name = atom->name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (strcmp(name, "subject") &&
		    strcmp(name, "body") &&
		    !starts_with(name, "trailers") &&
		    !starts_with(name, "contents"))
			continue;
		if (!subpos)
			find_subpos(buf,
				    &subpos, &sublen,
				    &bodypos, &bodylen, &nonsiglen,
				    &sigpos, &siglen);

		if (atom->u.contents.option == C_SUB)
			v->s = copy_subject(subpos, sublen);
		else if (atom->u.contents.option == C_BODY_DEP)
			v->s = xmemdupz(bodypos, bodylen);
		else if (atom->u.contents.option == C_BODY)
			v->s = xmemdupz(bodypos, nonsiglen);
		else if (atom->u.contents.option == C_SIG)
			v->s = xmemdupz(sigpos, siglen);
		else if (atom->u.contents.option == C_LINES) {
			struct strbuf s = STRBUF_INIT;
			const char *contents_end = bodylen + bodypos - siglen;

			/*  Size is the length of the message after removing the signature */
			append_lines(&s, subpos, contents_end - subpos, atom->u.contents.nlines);
			v->s = strbuf_detach(&s, NULL);
		} else if (atom->u.contents.option == C_TRAILERS) {
			struct strbuf s = STRBUF_INIT;

			/* Format the trailer info according to the trailer_opts given */
			format_trailers_from_commit(&s, subpos, &atom->u.contents.trailer_opts);

			v->s = strbuf_detach(&s, NULL);
		} else if (atom->u.contents.option == C_BARE)
			v->s = xstrdup(subpos);
	}
}