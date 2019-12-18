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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* get_builtin_ds () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
write_builtin_anchor(const char* file)
{
	const char* builtin_root_anchor = get_builtin_ds();
	FILE* out = fopen(file, "w");
	if(!out) {
		if(verb) printf("%s: %s\n", file, strerror(errno));
		if(verb) printf("  could not write builtin anchor\n");
		return;
	}
	if(!fwrite(builtin_root_anchor, strlen(builtin_root_anchor), 1, out)) {
		if(verb) printf("%s: %s\n", file, strerror(errno));
		if(verb) printf("  could not complete write builtin anchor\n");
	}
	fclose(out);
}