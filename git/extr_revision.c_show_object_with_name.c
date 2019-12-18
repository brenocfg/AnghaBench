#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct object {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ *) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 

void show_object_with_name(FILE *out, struct object *obj, const char *name)
{
	const char *p;

	fprintf(out, "%s ", oid_to_hex(&obj->oid));
	for (p = name; *p && *p != '\n'; p++)
		fputc(*p, out);
	fputc('\n', out);
}