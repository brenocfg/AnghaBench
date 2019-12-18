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
struct g_provider {int error; int /*<<< orphan*/ * private; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int zvol_close (struct g_provider*,int,int) ; 
 int zvol_open (struct g_provider*,int,int) ; 

__attribute__((used)) static int
zvol_geom_access(struct g_provider *pp, int acr, int acw, int ace)
{
	int count, error, flags;

	g_topology_assert();

	/*
	 * To make it easier we expect either open or close, but not both
	 * at the same time.
	 */
	KASSERT((acr >= 0 && acw >= 0 && ace >= 0) ||
	    (acr <= 0 && acw <= 0 && ace <= 0),
	    ("Unsupported access request to %s (acr=%d, acw=%d, ace=%d).",
	    pp->name, acr, acw, ace));

	if (pp->private == NULL) {
		if (acr <= 0 && acw <= 0 && ace <= 0)
			return (0);
		return (pp->error);
	}

	/*
	 * We don't pass FEXCL flag to zvol_open()/zvol_close() if ace != 0,
	 * because GEOM already handles that and handles it a bit differently.
	 * GEOM allows for multiple read/exclusive consumers and ZFS allows
	 * only one exclusive consumer, no matter if it is reader or writer.
	 * I like better the way GEOM works so I'll leave it for GEOM to
	 * decide what to do.
	 */

	count = acr + acw + ace;
	if (count == 0)
		return (0);

	flags = 0;
	if (acr != 0 || ace != 0)
		flags |= FREAD;
	if (acw != 0)
		flags |= FWRITE;

	g_topology_unlock();
	if (count > 0)
		error = zvol_open(pp, flags, count);
	else
		error = zvol_close(pp, flags, -count);
	g_topology_lock();
	return (error);
}