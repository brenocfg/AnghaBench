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
struct g_provider {int sectorsize; int /*<<< orphan*/  name; } ;
struct g_llvm_label {int dummy; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LLVM_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int llvm_label_decode (int /*<<< orphan*/ *,struct g_llvm_label*,int) ; 

int
g_llvm_read_label(struct g_consumer *cp, struct g_llvm_label *ll)
{
	struct g_provider *pp;
	u_char *buf;
	int i, error = 0;

	g_topology_assert();

	/* The LVM label is stored on the first four sectors */
	error = g_access(cp, 1, 0, 0);
	if (error != 0)
		return (error);
	pp = cp->provider;
	g_topology_unlock();
	buf = g_read_data(cp, 0, pp->sectorsize * 4, &error);
	g_topology_lock();
	g_access(cp, -1, 0, 0);
	if (buf == NULL) {
		G_LLVM_DEBUG(1, "Cannot read metadata from %s (error=%d)",
		    pp->name, error);
		return (error);
	}

	/* Search the four sectors for the LVM label. */
	for (i = 0; i < 4; i++) {
		error = llvm_label_decode(&buf[i * pp->sectorsize], ll, i);
		if (error == 0)
			break;	/* found it */
	}
	g_free(buf);
	return (error);
}