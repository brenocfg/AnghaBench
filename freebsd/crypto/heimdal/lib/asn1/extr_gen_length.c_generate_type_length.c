#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* gen_name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  codefile ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  length_type (char*,int /*<<< orphan*/ ,char*,char*) ; 

void
generate_type_length (const Symbol *s)
{
    fprintf (codefile,
	     "size_t ASN1CALL\n"
	     "length_%s(const %s *data)\n"
	     "{\n"
	     "size_t ret = 0;\n",
	     s->gen_name, s->gen_name);

    length_type ("data", s->type, "ret", "Top");
    fprintf (codefile, "return ret;\n}\n\n");
}