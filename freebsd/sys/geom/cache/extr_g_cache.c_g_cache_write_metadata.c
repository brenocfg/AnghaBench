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
struct g_consumer {struct g_provider* provider; } ;
struct g_cache_metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GCACHE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cache_metadata_encode (struct g_cache_metadata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int g_access (struct g_consumer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int g_write_data (struct g_consumer*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
g_cache_write_metadata(struct g_consumer *cp, struct g_cache_metadata *md)
{
	struct g_provider *pp;
	u_char *buf;
	int error;

	g_topology_assert();

	error = g_access(cp, 0, 1, 0);
	if (error != 0)
		return (error);
	pp = cp->provider;
	buf = malloc((size_t)pp->sectorsize, M_GCACHE, M_WAITOK | M_ZERO);
	cache_metadata_encode(md, buf);
	g_topology_unlock();
	error = g_write_data(cp, pp->mediasize - pp->sectorsize, buf, pp->sectorsize);
	g_topology_lock();
	g_access(cp, 0, -1, 0);
	free(buf, M_GCACHE);

	return (error);
}