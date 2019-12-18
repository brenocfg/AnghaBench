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
struct g_provider {int /*<<< orphan*/  name; scalar_t__ sectorsize; scalar_t__ mediasize; } ;
struct g_journal_metadata {scalar_t__ md_version; int /*<<< orphan*/  md_magic; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_JOURNAL_MAGIC ; 
 scalar_t__ G_JOURNAL_VERSION ; 
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int journal_metadata_decode (int /*<<< orphan*/ *,struct g_journal_metadata*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_journal_metadata_read(struct g_consumer *cp, struct g_journal_metadata *md)
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
	/* Metadata is stored in last sector. */
	buf = g_read_data(cp, pp->mediasize - pp->sectorsize, pp->sectorsize,
	    &error);
	g_topology_lock();
	g_access(cp, -1, 0, 0);
	if (buf == NULL) {
		GJ_DEBUG(1, "Cannot read metadata from %s (error=%d).",
		    cp->provider->name, error);
		return (error);
	}

	/* Decode metadata. */
	error = journal_metadata_decode(buf, md);
	g_free(buf);
	/* Is this is gjournal provider at all? */
	if (strcmp(md->md_magic, G_JOURNAL_MAGIC) != 0)
		return (EINVAL);
	/*
	 * Are we able to handle this version of metadata?
	 * We only maintain backward compatibility.
	 */
	if (md->md_version > G_JOURNAL_VERSION) {
		GJ_DEBUG(0,
		    "Kernel module is too old to handle metadata from %s.",
		    cp->provider->name);
		return (EINVAL);
	}
	/* Is checksum correct? */
	if (error != 0) {
		GJ_DEBUG(0, "MD5 metadata hash mismatch for provider %s.",
		    cp->provider->name);
		return (error);
	}
	return (0);
}