#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct g_virstor_softc {int /*<<< orphan*/  n_components; int /*<<< orphan*/  chunk_size; int /*<<< orphan*/  virsize; int /*<<< orphan*/  id; TYPE_1__* geom; struct g_virstor_component* components; } ;
struct g_virstor_metadata {size_t no; int /*<<< orphan*/  flags; int /*<<< orphan*/  chunk_reserved; int /*<<< orphan*/  chunk_next; int /*<<< orphan*/  chunk_count; int /*<<< orphan*/  provsize; int /*<<< orphan*/  provider; int /*<<< orphan*/  md_count; int /*<<< orphan*/  md_chunk_size; int /*<<< orphan*/  md_virsize; int /*<<< orphan*/  md_id; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
struct g_virstor_component {int /*<<< orphan*/  flags; int /*<<< orphan*/  chunk_reserved; int /*<<< orphan*/  chunk_next; int /*<<< orphan*/  chunk_count; TYPE_3__* gcons; } ;
struct TYPE_6__ {TYPE_2__* provider; } ;
struct TYPE_5__ {int /*<<< orphan*/  mediasize; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_VIRSTOR_MAGIC ; 
 int /*<<< orphan*/  G_VIRSTOR_VERSION ; 
 int /*<<< orphan*/  bzero (struct g_virstor_metadata*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fill_metadata(struct g_virstor_softc *sc, struct g_virstor_metadata *md,
    u_int nc, u_int hardcode)
{
	struct g_virstor_component *c;

	bzero(md, sizeof *md);
	c = &sc->components[nc];

	strncpy(md->md_magic, G_VIRSTOR_MAGIC, sizeof md->md_magic);
	md->md_version = G_VIRSTOR_VERSION;
	strncpy(md->md_name, sc->geom->name, sizeof md->md_name);
	md->md_id = sc->id;
	md->md_virsize = sc->virsize;
	md->md_chunk_size = sc->chunk_size;
	md->md_count = sc->n_components;

	if (hardcode) {
		strncpy(md->provider, c->gcons->provider->name,
		    sizeof md->provider);
	}
	md->no = nc;
	md->provsize = c->gcons->provider->mediasize;
	md->chunk_count = c->chunk_count;
	md->chunk_next = c->chunk_next;
	md->chunk_reserved = c->chunk_reserved;
	md->flags = c->flags;
}