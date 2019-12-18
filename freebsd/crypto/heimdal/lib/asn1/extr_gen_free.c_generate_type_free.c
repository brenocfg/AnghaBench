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
struct TYPE_3__ {char* gen_name; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  codefile ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_type (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ preserve_type (int /*<<< orphan*/ ) ; 

void
generate_type_free (const Symbol *s)
{
    int preserve = preserve_type(s->name) ? TRUE : FALSE;

    fprintf (codefile, "void ASN1CALL\n"
	     "free_%s(%s *data)\n"
	     "{\n",
	     s->gen_name, s->gen_name);

    free_type ("data", s->type, preserve);
    fprintf (codefile, "}\n\n");
}