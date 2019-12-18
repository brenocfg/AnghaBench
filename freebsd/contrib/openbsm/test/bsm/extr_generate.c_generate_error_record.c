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
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_NULL ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  au_errno_to_bsm (int) ; 
 int /*<<< orphan*/ * au_to_return32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  write_record (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
generate_error_record(const char *directory, const char *filename, int error)
{
	char pathname[PATH_MAX];
	token_t *return32_token;

	return32_token = au_to_return32(au_errno_to_bsm(error), -1);
	if (return32_token == NULL)
		err(EX_UNAVAILABLE, "au_to_return32");
	(void)snprintf(pathname, PATH_MAX, "%s_record", filename);
	write_record(directory, pathname, return32_token, AUE_NULL);
}