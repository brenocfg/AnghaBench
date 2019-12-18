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

/* Variables and functions */
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  VEF_VERBOSE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ manifest_open (char const*,unsigned char*) ; 
 unsigned char* verify_signed (char const*,int /*<<< orphan*/ ) ; 
 int yyparse () ; 

__attribute__((used)) static int
veriexec_load(const char *manifest)
{
	unsigned char *content;
	int rc;

	content = verify_signed(manifest, VEF_VERBOSE);
	if (!content)
		errx(EX_USAGE, "cannot verify %s", manifest);
	if (manifest_open(manifest, content)) {
		rc = yyparse();
	} else {
		err(EX_NOINPUT, "cannot load %s", manifest);
	}
	free(content);
	return (rc);
}