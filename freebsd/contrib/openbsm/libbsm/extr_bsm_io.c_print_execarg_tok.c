#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct TYPE_5__ {size_t count; int /*<<< orphan*/ * text; } ;
struct TYPE_6__ {TYPE_1__ execarg; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_xml_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_execarg_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{
	u_int32_t i;

	print_tok_type(fp, tok->id, "exec arg", oflags);
	for (i = 0; i < tok->tt.execarg.count; i++) {
		if (oflags & AU_OFLAG_XML) {
			fprintf(fp, "<arg>");
			print_xml_string(fp, tok->tt.execarg.text[i],
			    strlen(tok->tt.execarg.text[i]));
			fprintf(fp, "</arg>");
		} else {
			print_delim(fp, del);
			print_string(fp, tok->tt.execarg.text[i],
			    strlen(tok->tt.execarg.text[i]));
		}
	}
	if (oflags & AU_OFLAG_XML)
		close_tag(fp, tok->id);
}