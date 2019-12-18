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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_free (char*) ; 
 char* fn_tilde_expand (char const*) ; 
 int stat (char*,struct stat*) ; 

__attribute__((used)) static const char *
append_char_function(const char *name)
{
	struct stat stbuf;
	char *expname = *name == '~' ? fn_tilde_expand(name) : NULL;
	const char *rs = " ";

	if (stat(expname ? expname : name, &stbuf) == -1)
		goto out;
	if (S_ISDIR(stbuf.st_mode))
		rs = "/";
out:
	if (expname)
		el_free(expname);
	return rs;
}