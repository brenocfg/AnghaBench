#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* gen_name; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Symbol ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  gen_extern_stubs (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  generate_template_type (char*,char const**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_code_file () ; 
 scalar_t__ support_ber ; 
 scalar_t__ use_extern (TYPE_1__ const*) ; 

void
generate_template(const Symbol *s)
{
    FILE *f = get_code_file();
    const char *dupname;

    if (use_extern(s)) {
	gen_extern_stubs(f, s->gen_name);
	return;
    }

    generate_template_type(s->gen_name, &dupname, s->name, s->gen_name, NULL, s->type, 0, 0, 1);

    fprintf(f,
	    "\n"
	    "int\n"
	    "decode_%s(const unsigned char *p, size_t len, %s *data, size_t *size)\n"
	    "{\n"
	    "    return _asn1_decode_top(asn1_%s, 0|%s, p, len, data, size);\n"
	    "}\n"
	    "\n",
	    s->gen_name,
	    s->gen_name,
	    dupname,
	    support_ber ? "A1_PF_ALLOW_BER" : "0");

    fprintf(f,
	    "\n"
	    "int\n"
	    "encode_%s(unsigned char *p, size_t len, const %s *data, size_t *size)\n"
	    "{\n"
	    "    return _asn1_encode(asn1_%s, p, len, data, size);\n"
	    "}\n"
	    "\n",
	    s->gen_name,
	    s->gen_name,
	    dupname);

    fprintf(f,
	    "\n"
	    "size_t\n"
	    "length_%s(const %s *data)\n"
	    "{\n"
	    "    return _asn1_length(asn1_%s, data);\n"
	    "}\n"
	    "\n",
	    s->gen_name,
	    s->gen_name,
	    dupname);


    fprintf(f,
	    "\n"
	    "void\n"
	    "free_%s(%s *data)\n"
	    "{\n"
	    "    _asn1_free(asn1_%s, data);\n"
	    "}\n"
	    "\n",
	    s->gen_name,
	    s->gen_name,
	    dupname);

    fprintf(f,
	    "\n"
	    "int\n"
	    "copy_%s(const %s *from, %s *to)\n"
	    "{\n"
	    "    return _asn1_copy_top(asn1_%s, from, to);\n"
	    "}\n"
	    "\n",
	    s->gen_name,
	    s->gen_name,
	    s->gen_name,
	    dupname);
}