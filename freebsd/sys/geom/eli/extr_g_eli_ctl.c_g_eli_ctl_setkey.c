#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_eli_metadata {int md_iterations; int md_keys; int /*<<< orphan*/  md_keylen; int /*<<< orphan*/  md_ealgo; struct g_eli_metadata* md_mkeys; } ;
typedef  struct g_eli_metadata u_char ;
struct gctl_req {int dummy; } ;
struct g_provider {int sectorsize; char const* name; scalar_t__ mediasize; } ;
struct g_eli_softc {int sc_flags; int sc_nkey; int /*<<< orphan*/  sc_mkey; TYPE_1__* sc_geom; } ;
struct g_consumer {struct g_provider* provider; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  md ;
typedef  int intmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,int,char const*) ; 
 int G_ELI_FLAG_RO ; 
 int G_ELI_MAXMKEYS ; 
 int G_ELI_MKEYLEN ; 
 int G_ELI_USERKEYLEN ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ELI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct g_eli_metadata*,int) ; 
 int bitcount32 (int) ; 
 int /*<<< orphan*/  eli_metadata_encode (struct g_eli_metadata*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  explicit_bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  free (struct g_eli_metadata*,int /*<<< orphan*/ ) ; 
 struct g_eli_softc* g_eli_find_device (struct g_class*,char const*) ; 
 int g_eli_mkey_encrypt (int /*<<< orphan*/ ,struct g_eli_metadata*,int /*<<< orphan*/ ,struct g_eli_metadata*) ; 
 int g_eli_read_metadata (struct g_class*,struct g_provider*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int g_write_data (struct g_consumer*,scalar_t__,struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 struct g_eli_metadata* gctl_get_param (struct gctl_req*,char*,int*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 struct g_eli_metadata* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_eli_ctl_setkey(struct gctl_req *req, struct g_class *mp)
{
	struct g_eli_softc *sc;
	struct g_eli_metadata md;
	struct g_provider *pp;
	struct g_consumer *cp;
	const char *name;
	u_char *key, *mkeydst, *sector;
	intmax_t *valp;
	int keysize, nkey, error;

	g_topology_assert();

	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 0);
		return;
	}
	key = gctl_get_param(req, "key", &keysize);
	if (key == NULL || keysize != G_ELI_USERKEYLEN) {
		gctl_error(req, "No '%s' argument.", "key");
		return;
	}
	sc = g_eli_find_device(mp, name);
	if (sc == NULL) {
		gctl_error(req, "Provider %s is invalid.", name);
		return;
	}
	if (sc->sc_flags & G_ELI_FLAG_RO) {
		gctl_error(req, "Cannot change keys for read-only provider.");
		return;
	}
	cp = LIST_FIRST(&sc->sc_geom->consumer);
	pp = cp->provider;

	error = g_eli_read_metadata(mp, pp, &md);
	if (error != 0) {
		gctl_error(req, "Cannot read metadata from %s (error=%d).",
		    name, error);
		return;
	}

	valp = gctl_get_paraml(req, "keyno", sizeof(*valp));
	if (valp == NULL) {
		gctl_error(req, "No '%s' argument.", "keyno");
		return;
	}
	if (*valp != -1)
		nkey = *valp;
	else
		nkey = sc->sc_nkey;
	if (nkey < 0 || nkey >= G_ELI_MAXMKEYS) {
		gctl_error(req, "Invalid '%s' argument.", "keyno");
		return;
	}

	valp = gctl_get_paraml(req, "iterations", sizeof(*valp));
	if (valp == NULL) {
		gctl_error(req, "No '%s' argument.", "iterations");
		return;
	}
	/* Check if iterations number should and can be changed. */
	if (*valp != -1 && md.md_iterations == -1) {
		md.md_iterations = *valp;
	} else if (*valp != -1 && *valp != md.md_iterations) {
		if (bitcount32(md.md_keys) != 1) {
			gctl_error(req, "To be able to use '-i' option, only "
			    "one key can be defined.");
			return;
		}
		if (md.md_keys != (1 << nkey)) {
			gctl_error(req, "Only already defined key can be "
			    "changed when '-i' option is used.");
			return;
		}
		md.md_iterations = *valp;
	}

	mkeydst = md.md_mkeys + nkey * G_ELI_MKEYLEN;
	md.md_keys |= (1 << nkey);

	bcopy(sc->sc_mkey, mkeydst, sizeof(sc->sc_mkey));

	/* Encrypt Master Key with the new key. */
	error = g_eli_mkey_encrypt(md.md_ealgo, key, md.md_keylen, mkeydst);
	explicit_bzero(key, keysize);
	if (error != 0) {
		explicit_bzero(&md, sizeof(md));
		gctl_error(req, "Cannot encrypt Master Key (error=%d).", error);
		return;
	}

	sector = malloc(pp->sectorsize, M_ELI, M_WAITOK | M_ZERO);
	/* Store metadata with fresh key. */
	eli_metadata_encode(&md, sector);
	explicit_bzero(&md, sizeof(md));
	error = g_write_data(cp, pp->mediasize - pp->sectorsize, sector,
	    pp->sectorsize);
	explicit_bzero(sector, pp->sectorsize);
	free(sector, M_ELI);
	if (error != 0) {
		gctl_error(req, "Cannot store metadata on %s (error=%d).",
		    pp->name, error);
		return;
	}
	G_ELI_DEBUG(1, "Key %u changed on %s.", nkey, pp->name);
}