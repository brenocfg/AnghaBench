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
struct ngtype {int dummy; } ;

/* Variables and functions */
 struct ngtype* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ngtype*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/ * csock_fd ; 
 int /*<<< orphan*/  dsock ; 
 int /*<<< orphan*/ * dsock_fd ; 
 int /*<<< orphan*/  fd_deselect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ngtype*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  ngtype_list ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_index ; 
 struct ngtype* snmp_nodename ; 

__attribute__((used)) static int
ng_fini(void)
{
	struct ngtype *t;

	while ((t = TAILQ_FIRST(&ngtype_list)) != NULL) {
		TAILQ_REMOVE(&ngtype_list, t, link);
		free(t);
	}

	if (csock_fd != NULL)
		fd_deselect(csock_fd);
	(void)close(csock);

	if (dsock_fd != NULL)
		fd_deselect(dsock_fd);
	(void)close(dsock);

	free(snmp_nodename);

	or_unregister(reg_index);

	return (0);
}