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
typedef  int /*<<< orphan*/  u_char ;
struct g_provider {scalar_t__ sectorsize; scalar_t__ mediasize; } ;
struct g_multipath_metadata {int dummy; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  multipath_metadata_decode (int /*<<< orphan*/ *,struct g_multipath_metadata*) ; 

__attribute__((used)) static int
g_multipath_read_metadata(struct g_consumer *cp,
    struct g_multipath_metadata *md)
{
	struct g_provider *pp;
	u_char *buf;
	int error;

	g_topology_assert();
	error = g_access(cp, 1, 0, 0);
	if (error != 0)
		return (error);
	pp = cp->provider;
	g_topology_unlock();
	buf = g_read_data(cp, pp->mediasize - pp->sectorsize,
	    pp->sectorsize, &error);
	g_topology_lock();
	g_access(cp, -1, 0, 0);
	if (buf == NULL)
		return (error);
	multipath_metadata_decode(buf, md);
	g_free(buf);
	return (0);
}