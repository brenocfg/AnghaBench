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
 scalar_t__ ERR_GET_FUNC (unsigned long) ; 
 scalar_t__ ERR_GET_LIB (unsigned long) ; 
 scalar_t__ ERR_LIB_SYS ; 
 unsigned long ERR_peek_error () ; 
 char* ERR_reason_error_string (unsigned long) ; 
 scalar_t__ SYS_F_FOPEN ; 
 scalar_t__ SYS_F_FREAD ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  ssl_err (char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ssl_path_err(const char* s, const char *path)
{
	unsigned long err;
	err = ERR_peek_error();
	if (ERR_GET_LIB(err) == ERR_LIB_SYS &&
		(ERR_GET_FUNC(err) == SYS_F_FOPEN ||
		 ERR_GET_FUNC(err) == SYS_F_FREAD) ) {
		fprintf(stderr, "error: %s\n%s: %s\n",
			s, path, ERR_reason_error_string(err));
		exit(1);
	} else {
		ssl_err(s);
	}
}