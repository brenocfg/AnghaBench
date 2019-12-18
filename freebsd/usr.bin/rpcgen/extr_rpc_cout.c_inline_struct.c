#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* decls; } ;
struct TYPE_11__ {TYPE_1__ st; } ;
struct TYPE_12__ {TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;
struct TYPE_15__ {scalar_t__ rel; int /*<<< orphan*/  array_max; int /*<<< orphan*/  type; int /*<<< orphan*/ * prefix; } ;
struct TYPE_13__ {struct TYPE_13__* next; TYPE_6__ decl; } ;
typedef  TYPE_4__ decl_list ;
struct TYPE_14__ {int length; } ;
typedef  TYPE_5__ bas_type ;

/* Variables and functions */
 int PUT ; 
 scalar_t__ REL_ALIAS ; 
 scalar_t__ REL_VECTOR ; 
 int /*<<< orphan*/  emit_inline (int,TYPE_6__*,int) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_5__* find_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (char*) ; 
 int inline_size ; 
 int /*<<< orphan*/  print_stat (int,TYPE_6__*) ; 
 int /*<<< orphan*/  s_print (char*,char*,char const*,int /*<<< orphan*/ ,...) ; 
 char* strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  tabify (int /*<<< orphan*/ ,int) ; 
 char* xrealloc (char*,scalar_t__) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
inline_struct(definition *def, int flag)
{
	decl_list *dl;
	int i, size;
	decl_list *cur, *psav;
	bas_type *ptr;
	char *sizestr;
	const char *plus;
	char ptemp[256];
	int indent = 1;

	cur = NULL;
	if (flag == PUT)
		f_print(fout, "\n\tif (xdrs->x_op == XDR_ENCODE) {\n");
	else
		f_print(fout, "\t\treturn (TRUE);\n\t} else if (xdrs->x_op == XDR_DECODE) {\n");

	i = 0;
	size = 0;
	sizestr = NULL;
	for (dl = def->def.st.decls; dl != NULL; dl = dl->next) { /* xxx */
		/* now walk down the list and check for basic types */
		if ((dl->decl.prefix == NULL) &&
		    ((ptr = find_type(dl->decl.type)) != NULL) &&
		    ((dl->decl.rel == REL_ALIAS) ||
		     (dl->decl.rel == REL_VECTOR))){
			if (i == 0)
				cur = dl;
			i++;

			if (dl->decl.rel == REL_ALIAS)
				size += ptr->length;
			else {
				/* this code is required to handle arrays */
				if (sizestr == NULL)
					plus = "";
				else
					plus = " + ";

				if (ptr->length != 1)
					s_print(ptemp, "%s%s * %d",
						plus, dl->decl.array_max,
						ptr->length);
				else
					s_print(ptemp, "%s%s", plus,
						dl->decl.array_max);

				/* now concatenate to sizestr !!!! */
				if (sizestr == NULL) {
					sizestr = xstrdup(ptemp);
				}
				else{
					sizestr = xrealloc(sizestr,
							  strlen(sizestr)
							  +strlen(ptemp)+1);
					sizestr = strcat(sizestr, ptemp);
					/* build up length of array */
				}
			}
		} else {
			if (i > 0) {
				if (sizestr == NULL && size < inline_size){
					/*
					 * don't expand into inline code
					 * if size < inline_size
					 */
					while (cur != dl){
						print_stat(indent + 1, &cur->decl);
						cur = cur->next;
					}
				} else {
					/* were already looking at a xdr_inlineable structure */
					tabify(fout, indent + 1);
					if (sizestr == NULL)
						f_print(fout, "buf = XDR_INLINE(xdrs, %d * BYTES_PER_XDR_UNIT);",
							size);
					else {
						if (size == 0)
							f_print(fout,
								"buf = XDR_INLINE(xdrs, (%s) * BYTES_PER_XDR_UNIT);",
								sizestr);
						else
							f_print(fout,
								"buf = XDR_INLINE(xdrs, (%d + (%s)) * BYTES_PER_XDR_UNIT);",
								size, sizestr);

					}
					f_print(fout, "\n");
					tabify(fout, indent + 1);
					f_print(fout,
						"if (buf == NULL) {\n");

					psav = cur;
					while (cur != dl){
						print_stat(indent + 2, &cur->decl);
						cur = cur->next;
					}

					f_print(fout, "\n\t\t} else {\n");

					cur = psav;
					while (cur != dl){
						emit_inline(indent + 2, &cur->decl, flag);
						cur = cur->next;
					}

					tabify(fout, indent + 1);
					f_print(fout, "}\n");
				}
			}
			size = 0;
			i = 0;
			free(sizestr);
			sizestr = NULL;
			print_stat(indent + 1, &dl->decl);
		}
	}

	if (i > 0) {
		if (sizestr == NULL && size < inline_size){
			/* don't expand into inline code if size < inline_size */
			while (cur != dl){
				print_stat(indent + 1, &cur->decl);
				cur = cur->next;
			}
		} else {
			/* were already looking at a xdr_inlineable structure */
			if (sizestr == NULL)
				f_print(fout, "\t\tbuf = XDR_INLINE(xdrs, %d * BYTES_PER_XDR_UNIT);",
					size);
			else
				if (size == 0)
					f_print(fout,
						"\t\tbuf = XDR_INLINE(xdrs, (%s) * BYTES_PER_XDR_UNIT);",
						sizestr);
				else
					f_print(fout,
						"\t\tbuf = XDR_INLINE(xdrs, (%d + (%s)) * BYTES_PER_XDR_UNIT);",
						size, sizestr);

			f_print(fout, "\n\t\tif (buf == NULL) {\n");
			psav = cur;
			while (cur != NULL){
				print_stat(indent + 2, &cur->decl);
				cur = cur->next;
			}
			f_print(fout, "\t\t} else {\n");

			cur = psav;
			while (cur != dl){
				emit_inline(indent + 2, &cur->decl, flag);
				cur = cur->next;
			}
			f_print(fout, "\t\t}\n");
		}
	}
}