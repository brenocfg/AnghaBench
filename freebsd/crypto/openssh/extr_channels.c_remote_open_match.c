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
struct permission {scalar_t__ listen_port; int /*<<< orphan*/ * listen_host; } ;
struct Forward {scalar_t__ listen_port; int /*<<< orphan*/ * listen_host; int /*<<< orphan*/ * listen_path; } ;

/* Variables and functions */
 scalar_t__ FWD_PERMIT_ANY_PORT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lowercase (char*) ; 
 int match_pattern (char*,int /*<<< orphan*/ *) ; 
 char* xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
remote_open_match(struct permission *allowed_open, struct Forward *fwd)
{
	int ret;
	char *lhost;

	/* XXX add ACLs for streamlocal */
	if (fwd->listen_path != NULL)
		return 1;

	if (fwd->listen_host == NULL || allowed_open->listen_host == NULL)
		return 0;

	if (allowed_open->listen_port != FWD_PERMIT_ANY_PORT &&
	    allowed_open->listen_port != fwd->listen_port)
		return 0;

	/* Match hostnames case-insensitively */
	lhost = xstrdup(fwd->listen_host);
	lowercase(lhost);
	ret = match_pattern(lhost, allowed_open->listen_host);
	free(lhost);

	return ret;
}