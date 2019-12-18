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
struct section {int dummy; } ;
struct reg {char* subkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_defaultinfo (struct section const*,struct reg const*,int) ; 
 int /*<<< orphan*/  dump_paramdesc (struct section const*,struct reg const*) ; 
 int /*<<< orphan*/  dump_typeinfo (struct section const*,struct reg const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ofp ; 
 int strlen (char*) ; 

__attribute__((used)) static void
dump_paramreg(const struct section *s, const struct reg *r, int devidx)
{
	const char *keyname;

	keyname = r->subkey + strlen("Ndi\\params\\");
	fprintf(ofp, "\n\t{ \"%s\",", keyname);
	dump_paramdesc(s, r);
	dump_typeinfo(s, r);
	fprintf(ofp, "\",");
	dump_defaultinfo(s, r, devidx);

	return;
}