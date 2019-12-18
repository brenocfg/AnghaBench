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
typedef  int u_int ;
struct nm_hash_ent {int dummy; } ;
struct netmap_bdg_ops {int /*<<< orphan*/  name; } ;
struct nm_bridge {int bdg_flags; scalar_t__ bdg_active_ports; int bdg_namelen; int* bdg_port_index; int /*<<< orphan*/ * ht; int /*<<< orphan*/ * private_data; struct netmap_bdg_ops bdg_saved_ops; struct netmap_bdg_ops bdg_ops; int /*<<< orphan*/  bdg_basename; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMG_LOCK_ASSERT () ; 
 int NM_BDG_ACTIVE ; 
 int NM_BDG_HASH ; 
 int NM_BDG_MAXPORTS ; 
 int /*<<< orphan*/  NM_BNS_GET (struct nm_bridge*) ; 
 int /*<<< orphan*/  netmap_bns_getbridges (struct nm_bridge**,int*) ; 
 int nm_bdg_name_validate (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nm_os_malloc (int) ; 
 int /*<<< orphan*/  nm_prdis (char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  nm_prerr (char*,...) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

struct nm_bridge *
nm_find_bridge(const char *name, int create, struct netmap_bdg_ops *ops)
{
	int i, namelen;
	struct nm_bridge *b = NULL, *bridges;
	u_int num_bridges;

	NMG_LOCK_ASSERT();

	netmap_bns_getbridges(&bridges, &num_bridges);

	namelen = nm_bdg_name_validate(name,
			(ops != NULL ? strlen(ops->name) : 0));
	if (namelen < 0) {
		nm_prerr("invalid bridge name %s", name ? name : NULL);
		return NULL;
	}

	/* lookup the name, remember empty slot if there is one */
	for (i = 0; i < num_bridges; i++) {
		struct nm_bridge *x = bridges + i;

		if ((x->bdg_flags & NM_BDG_ACTIVE) + x->bdg_active_ports == 0) {
			if (create && b == NULL)
				b = x;	/* record empty slot */
		} else if (x->bdg_namelen != namelen) {
			continue;
		} else if (strncmp(name, x->bdg_basename, namelen) == 0) {
			nm_prdis("found '%.*s' at %d", namelen, name, i);
			b = x;
			break;
		}
	}
	if (i == num_bridges && b) { /* name not found, can create entry */
		/* initialize the bridge */
		nm_prdis("create new bridge %s with ports %d", b->bdg_basename,
			b->bdg_active_ports);
		b->ht = nm_os_malloc(sizeof(struct nm_hash_ent) * NM_BDG_HASH);
		if (b->ht == NULL) {
			nm_prerr("failed to allocate hash table");
			return NULL;
		}
		strncpy(b->bdg_basename, name, namelen);
		b->bdg_namelen = namelen;
		b->bdg_active_ports = 0;
		for (i = 0; i < NM_BDG_MAXPORTS; i++)
			b->bdg_port_index[i] = i;
		/* set the default function */
		b->bdg_ops = b->bdg_saved_ops = *ops;
		b->private_data = b->ht;
		b->bdg_flags = 0;
		NM_BNS_GET(b);
	}
	return b;
}