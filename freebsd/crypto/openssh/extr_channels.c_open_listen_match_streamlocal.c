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
struct permission {scalar_t__ listen_port; int /*<<< orphan*/ * listen_path; int /*<<< orphan*/ * host_to_connect; } ;

/* Variables and functions */
 scalar_t__ PORT_STREAMLOCAL ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
open_listen_match_streamlocal(struct permission *allowed_open,
    const char *requestedpath)
{
	if (allowed_open->host_to_connect == NULL)
		return 0;
	if (allowed_open->listen_port != PORT_STREAMLOCAL)
		return 0;
	if (allowed_open->listen_path == NULL ||
	    strcmp(allowed_open->listen_path, requestedpath) != 0)
		return 0;
	return 1;
}