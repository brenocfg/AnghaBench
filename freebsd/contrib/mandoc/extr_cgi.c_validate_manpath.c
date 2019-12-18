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
struct req {size_t psz; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
validate_manpath(const struct req *req, const char* manpath)
{
	size_t	 i;

	for (i = 0; i < req->psz; i++)
		if ( ! strcmp(manpath, req->p[i]))
			return 1;

	return 0;
}