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
typedef  char* uintmax_t ;
struct sbuf {int dummy; } ;
struct g_provider {int dummy; } ;
struct g_geom {struct g_eli_softc* softc; } ;
struct g_eli_softc {int sc_flags; char* sc_nkey; char* sc_version; int sc_crypto; char* sc_ekeylen; int /*<<< orphan*/  sc_ealgo; int /*<<< orphan*/  sc_aalgo; scalar_t__ sc_ekeys_allocated; scalar_t__ sc_ekeys_total; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_FLAG (int,char*) ; 
#define  G_ELI_CRYPTO_HW 129 
#define  G_ELI_CRYPTO_SW 128 
 int G_ELI_FLAG_AUTH ; 
 int G_ELI_FLAG_AUTORESIZE ; 
 int G_ELI_FLAG_BOOT ; 
 int G_ELI_FLAG_DESTROY ; 
 int G_ELI_FLAG_GELIBOOT ; 
 int G_ELI_FLAG_GELIDISPLAYPASS ; 
 int G_ELI_FLAG_NATIVE_BYTE_ORDER ; 
 int G_ELI_FLAG_NODELETE ; 
 int G_ELI_FLAG_ONETIME ; 
 int G_ELI_FLAG_RO ; 
 int G_ELI_FLAG_RW_DETACH ; 
 int G_ELI_FLAG_SINGLE_KEY ; 
 int G_ELI_FLAG_SUSPEND ; 
 int G_ELI_FLAG_WOPEN ; 
 int G_ELI_FLAG_WO_DETACH ; 
 char* g_eli_algo2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 

__attribute__((used)) static void
g_eli_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	struct g_eli_softc *sc;

	g_topology_assert();
	sc = gp->softc;
	if (sc == NULL)
		return;
	if (pp != NULL || cp != NULL)
		return;	/* Nothing here. */

	sbuf_printf(sb, "%s<KeysTotal>%ju</KeysTotal>\n", indent,
	    (uintmax_t)sc->sc_ekeys_total);
	sbuf_printf(sb, "%s<KeysAllocated>%ju</KeysAllocated>\n", indent,
	    (uintmax_t)sc->sc_ekeys_allocated);
	sbuf_printf(sb, "%s<Flags>", indent);
	if (sc->sc_flags == 0)
		sbuf_cat(sb, "NONE");
	else {
		int first = 1;

#define ADD_FLAG(flag, name)	do {					\
	if (sc->sc_flags & (flag)) {					\
		if (!first)						\
			sbuf_cat(sb, ", ");				\
		else							\
			first = 0;					\
		sbuf_cat(sb, name);					\
	}								\
} while (0)
		ADD_FLAG(G_ELI_FLAG_SUSPEND, "SUSPEND");
		ADD_FLAG(G_ELI_FLAG_SINGLE_KEY, "SINGLE-KEY");
		ADD_FLAG(G_ELI_FLAG_NATIVE_BYTE_ORDER, "NATIVE-BYTE-ORDER");
		ADD_FLAG(G_ELI_FLAG_ONETIME, "ONETIME");
		ADD_FLAG(G_ELI_FLAG_BOOT, "BOOT");
		ADD_FLAG(G_ELI_FLAG_WO_DETACH, "W-DETACH");
		ADD_FLAG(G_ELI_FLAG_RW_DETACH, "RW-DETACH");
		ADD_FLAG(G_ELI_FLAG_AUTH, "AUTH");
		ADD_FLAG(G_ELI_FLAG_WOPEN, "W-OPEN");
		ADD_FLAG(G_ELI_FLAG_DESTROY, "DESTROY");
		ADD_FLAG(G_ELI_FLAG_RO, "READ-ONLY");
		ADD_FLAG(G_ELI_FLAG_NODELETE, "NODELETE");
		ADD_FLAG(G_ELI_FLAG_GELIBOOT, "GELIBOOT");
		ADD_FLAG(G_ELI_FLAG_GELIDISPLAYPASS, "GELIDISPLAYPASS");
		ADD_FLAG(G_ELI_FLAG_AUTORESIZE, "AUTORESIZE");
#undef  ADD_FLAG
	}
	sbuf_cat(sb, "</Flags>\n");

	if (!(sc->sc_flags & G_ELI_FLAG_ONETIME)) {
		sbuf_printf(sb, "%s<UsedKey>%u</UsedKey>\n", indent,
		    sc->sc_nkey);
	}
	sbuf_printf(sb, "%s<Version>%u</Version>\n", indent, sc->sc_version);
	sbuf_printf(sb, "%s<Crypto>", indent);
	switch (sc->sc_crypto) {
	case G_ELI_CRYPTO_HW:
		sbuf_cat(sb, "hardware");
		break;
	case G_ELI_CRYPTO_SW:
		sbuf_cat(sb, "software");
		break;
	default:
		sbuf_cat(sb, "UNKNOWN");
		break;
	}
	sbuf_cat(sb, "</Crypto>\n");
	if (sc->sc_flags & G_ELI_FLAG_AUTH) {
		sbuf_printf(sb,
		    "%s<AuthenticationAlgorithm>%s</AuthenticationAlgorithm>\n",
		    indent, g_eli_algo2str(sc->sc_aalgo));
	}
	sbuf_printf(sb, "%s<KeyLength>%u</KeyLength>\n", indent,
	    sc->sc_ekeylen);
	sbuf_printf(sb, "%s<EncryptionAlgorithm>%s</EncryptionAlgorithm>\n",
	    indent, g_eli_algo2str(sc->sc_ealgo));
	sbuf_printf(sb, "%s<State>%s</State>\n", indent,
	    (sc->sc_flags & G_ELI_FLAG_SUSPEND) ? "SUSPENDED" : "ACTIVE");
}