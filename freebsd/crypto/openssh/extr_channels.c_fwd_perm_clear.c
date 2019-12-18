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
struct permission {int /*<<< orphan*/  listen_path; int /*<<< orphan*/  listen_host; int /*<<< orphan*/  host_to_connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct permission*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fwd_perm_clear(struct permission *perm)
{
	free(perm->host_to_connect);
	free(perm->listen_host);
	free(perm->listen_path);
	bzero(perm, sizeof(*perm));
}