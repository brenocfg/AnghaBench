#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* gen_name; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Symbol ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  close_codefile () ; 
 int /*<<< orphan*/ * codefile ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  generate_glue (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generate_header_of_codefile (char*) ; 
 int /*<<< orphan*/  generate_template (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_copy (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_decode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_encode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_free (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_header (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_length (TYPE_1__ const*) ; 
 int /*<<< orphan*/  generate_type_seq (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * headerfile ; 
 scalar_t__ is_export (int /*<<< orphan*/ ) ; 
 scalar_t__ is_template_compat (TYPE_1__ const*) ; 
 int /*<<< orphan*/  one_code_file ; 
 int /*<<< orphan*/ * privheaderfile ; 
 scalar_t__ template_flag ; 

void
generate_type (const Symbol *s)
{
    FILE *h;
    const char * exp;

    if (!one_code_file)
	generate_header_of_codefile(s->gen_name);

    generate_type_header (s);

    if (template_flag)
	generate_template(s);

    if (template_flag == 0 || is_template_compat(s) == 0) {
	generate_type_encode (s);
	generate_type_decode (s);
	generate_type_free (s);
	generate_type_length (s);
	generate_type_copy (s);
    }
    generate_type_seq (s);
    generate_glue (s->type, s->gen_name);

    /* generate prototypes */

    if (is_export(s->name)) {
	h = headerfile;
	exp = "ASN1EXP ";
    } else {
	h = privheaderfile;
	exp = "";
    }

    fprintf (h,
	     "%sint    ASN1CALL "
	     "decode_%s(const unsigned char *, size_t, %s *, size_t *);\n",
	     exp,
	     s->gen_name, s->gen_name);
    fprintf (h,
	     "%sint    ASN1CALL "
	     "encode_%s(unsigned char *, size_t, const %s *, size_t *);\n",
	     exp,
	     s->gen_name, s->gen_name);
    fprintf (h,
	     "%ssize_t ASN1CALL length_%s(const %s *);\n",
	     exp,
	     s->gen_name, s->gen_name);
    fprintf (h,
	     "%sint    ASN1CALL copy_%s  (const %s *, %s *);\n",
	     exp,
	     s->gen_name, s->gen_name, s->gen_name);
    fprintf (h,
	     "%svoid   ASN1CALL free_%s  (%s *);\n",
	     exp,
	     s->gen_name, s->gen_name);

    fprintf(h, "\n\n");

    if (!one_code_file) {
	fprintf(codefile, "\n\n");
	close_codefile();
	}
}