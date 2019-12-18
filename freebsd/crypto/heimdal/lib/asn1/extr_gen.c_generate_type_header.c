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
struct TYPE_3__ {char* name; int /*<<< orphan*/  type; int /*<<< orphan*/  gen_name; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  define_asn1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  headerfile ; 
 scalar_t__ preserve_type (char*) ; 

__attribute__((used)) static void
generate_type_header (const Symbol *s)
{
    int preservep = preserve_type(s->name) ? TRUE : FALSE;

    fprintf (headerfile, "/*\n");
    fprintf (headerfile, "%s ::= ", s->name);
    define_asn1 (0, s->type);
    fprintf (headerfile, "\n*/\n\n");

    fprintf (headerfile, "typedef ");
    define_type (0, s->gen_name, s->gen_name, s->type, TRUE, preservep);

    fprintf (headerfile, "\n");
}