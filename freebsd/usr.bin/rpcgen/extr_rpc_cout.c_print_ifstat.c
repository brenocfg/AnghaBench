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
typedef  int relation ;

/* Variables and functions */
#define  REL_ALIAS 131 
#define  REL_ARRAY 130 
#define  REL_POINTER 129 
#define  REL_VECTOR 128 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  print_ifarg (char const*) ; 
 int /*<<< orphan*/  print_ifclose (int,int) ; 
 int /*<<< orphan*/  print_ifopen (int,char const*) ; 
 int /*<<< orphan*/  print_ifsizeof (int,char const*,char const*) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 

__attribute__((used)) static void
print_ifstat(int indent, const char *prefix, const char *type, relation rel,
    const char *amax, const char *objname, const char *name)
{
	const char *alt = NULL;
	int brace = 0;

	switch (rel) {
	case REL_POINTER:
		brace = 1;
		f_print(fout, "\t{\n");
		f_print(fout, "\t%s **pp = %s;\n", type, objname);
		print_ifopen(indent, "pointer");
		print_ifarg("(char **)");
		f_print(fout, "pp");
		print_ifsizeof(0, prefix, type);
		break;
	case REL_VECTOR:
		if (streq(type, "string")) {
			alt = "string";
		} else if (streq(type, "opaque")) {
			alt = "opaque";
		}
		if (alt) {
			print_ifopen(indent, alt);
			print_ifarg(objname);
		} else {
			print_ifopen(indent, "vector");
			print_ifarg("(char *)");
			f_print(fout, "%s", objname);
		}
		print_ifarg(amax);
		if (!alt) {
			print_ifsizeof(indent + 1, prefix, type);
		}
		break;
	case REL_ARRAY:
		if (streq(type, "string")) {
			alt = "string";
		} else if (streq(type, "opaque")) {
			alt = "bytes";
		}
		if (streq(type, "string")) {
			print_ifopen(indent, alt);
			print_ifarg(objname);
		} else {
			if (alt) {
				print_ifopen(indent, alt);
			} else {
				print_ifopen(indent, "array");
			}
			print_ifarg("(char **)");
			if (*objname == '&') {
				f_print(fout, "%s.%s_val, (u_int *) %s.%s_len",
					objname, name, objname, name);
			} else {
				f_print(fout,
					"&%s->%s_val, (u_int *) &%s->%s_len",
					objname, name, objname, name);
			}
		}
		print_ifarg(amax);
		if (!alt) {
			print_ifsizeof(indent + 1, prefix, type);
		}
		break;
	case REL_ALIAS:
		print_ifopen(indent, type);
		print_ifarg(objname);
		break;
	}
	print_ifclose(indent, brace);
}