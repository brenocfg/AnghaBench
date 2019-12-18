#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct client_lease {struct client_lease* next; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_5__ {TYPE_1__* client; } ;
struct TYPE_4__ {struct client_lease* active; struct client_lease* leases; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FCNTL ; 
 int /*<<< orphan*/  CAP_FCNTL_GETFL ; 
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_FSYNC ; 
 int /*<<< orphan*/  CAP_FTRUNCATE ; 
 int /*<<< orphan*/  CAP_SEEK ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_fcntls_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftello (scalar_t__) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ifi ; 
 scalar_t__ leaseFile ; 
 int /*<<< orphan*/  path_dhclient_db ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 
 int /*<<< orphan*/  write_client_lease (TYPE_2__*,struct client_lease*,int) ; 

void
rewrite_client_leases(void)
{
	struct client_lease *lp;
	cap_rights_t rights;

	if (!leaseFile) {
		leaseFile = fopen(path_dhclient_db, "w");
		if (!leaseFile)
			error("can't create %s: %m", path_dhclient_db);
		cap_rights_init(&rights, CAP_FCNTL, CAP_FSTAT, CAP_FSYNC,
		    CAP_FTRUNCATE, CAP_SEEK, CAP_WRITE);
		if (caph_rights_limit(fileno(leaseFile), &rights) < 0) {
			error("can't limit lease descriptor: %m");
		}
		if (caph_fcntls_limit(fileno(leaseFile), CAP_FCNTL_GETFL) < 0) {
			error("can't limit lease descriptor fcntls: %m");
		}
	} else {
		fflush(leaseFile);
		rewind(leaseFile);
	}

	for (lp = ifi->client->leases; lp; lp = lp->next)
		write_client_lease(ifi, lp, 1);
	if (ifi->client->active)
		write_client_lease(ifi, ifi->client->active, 1);

	fflush(leaseFile);
	ftruncate(fileno(leaseFile), ftello(leaseFile));
	fsync(fileno(leaseFile));
}