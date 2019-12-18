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
typedef  char u_char ;
struct g_provider {int sectorsize; int /*<<< orphan*/  name; } ;
struct g_llvm_metadata {int md_relsize; int /*<<< orphan*/  md_reloffset; } ;
struct g_llvm_label {int /*<<< orphan*/  ll_md_offset; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LLVM_DEBUG (int,char*,char*,...) ; 
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int llvm_md_decode (char*,struct g_llvm_metadata*,struct g_llvm_label*) ; 
 int llvm_textconf_decode (char*,size_t,struct g_llvm_metadata*) ; 

int
g_llvm_read_md(struct g_consumer *cp, struct g_llvm_metadata *md,
    struct g_llvm_label *ll)
{
	struct g_provider *pp;
	u_char *buf;
	int error;
	int size;

	g_topology_assert();

	error = g_access(cp, 1, 0, 0);
	if (error != 0)
		return (error);
	pp = cp->provider;
	g_topology_unlock();
	buf = g_read_data(cp, ll->ll_md_offset, pp->sectorsize, &error);
	g_topology_lock();
	g_access(cp, -1, 0, 0);
	if (buf == NULL) {
		G_LLVM_DEBUG(0, "Cannot read metadata from %s (error=%d)",
		    cp->provider->name, error);
		return (error);
	}

	error = llvm_md_decode(buf, md, ll);
	g_free(buf);
	if (error != 0) {
		return (error);
	}

	G_LLVM_DEBUG(1, "reading LVM2 config @ %s:%ju", pp->name,
		    ll->ll_md_offset + md->md_reloffset);
	error = g_access(cp, 1, 0, 0);
	if (error != 0)
		return (error);
	pp = cp->provider;
	g_topology_unlock();
	/* round up to the nearest sector */
	size = md->md_relsize +
	    (pp->sectorsize - md->md_relsize % pp->sectorsize);
	buf = g_read_data(cp, ll->ll_md_offset + md->md_reloffset, size, &error);
	g_topology_lock();
	g_access(cp, -1, 0, 0);
	if (buf == NULL) {
		G_LLVM_DEBUG(0, "Cannot read LVM2 config from %s (error=%d)",
		    pp->name, error);
		return (error);
	}
	buf[md->md_relsize] = '\0';
	G_LLVM_DEBUG(10, "LVM config:\n%s\n", buf);
	error = llvm_textconf_decode(buf, md->md_relsize, md);
	g_free(buf);

	return (error);
}