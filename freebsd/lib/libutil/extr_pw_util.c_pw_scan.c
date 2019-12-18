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
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pw_initpwd (struct passwd*) ; 
 int /*<<< orphan*/  __pw_scan (char*,struct passwd*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct passwd* pw_dup (struct passwd*) ; 
 char* strdup (char const*) ; 

struct passwd *
pw_scan(const char *line, int flags)
{
	struct passwd pw, *ret;
	char *bp;

	if ((bp = strdup(line)) == NULL)
		return (NULL);
	__pw_initpwd(&pw);
	if (!__pw_scan(bp, &pw, flags)) {
		free(bp);
		return (NULL);
	}
	ret = pw_dup(&pw);
	free(bp);
	return (ret);
}