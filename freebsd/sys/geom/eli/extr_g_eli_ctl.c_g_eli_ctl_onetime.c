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
struct g_eli_metadata {scalar_t__ md_ealgo; scalar_t__ md_aalgo; scalar_t__ md_keylen; int md_keys; int md_sectorsize; struct g_eli_metadata* md_hash; struct g_eli_metadata* md_salt; scalar_t__ md_provsize; int /*<<< orphan*/  md_flags; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
typedef  struct g_eli_metadata u_char ;
struct gctl_req {int dummy; } ;
struct g_provider {int sectorsize; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  mkey ;
typedef  int /*<<< orphan*/  md ;
typedef  int intmax_t ;

/* Variables and functions */
 scalar_t__ CRYPTO_ALGORITHM_MAX ; 
 scalar_t__ CRYPTO_ALGORITHM_MIN ; 
 int G_ELI_DATAIVKEYLEN ; 
 int /*<<< orphan*/  G_ELI_FLAG_AUTH ; 
 int /*<<< orphan*/  G_ELI_FLAG_AUTORESIZE ; 
 int /*<<< orphan*/  G_ELI_FLAG_NODELETE ; 
 int /*<<< orphan*/  G_ELI_FLAG_ONETIME ; 
 int /*<<< orphan*/  G_ELI_FLAG_WO_DETACH ; 
 int /*<<< orphan*/  G_ELI_MAGIC ; 
 int /*<<< orphan*/  G_ELI_VERSION ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  arc4rand (struct g_eli_metadata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  explicit_bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  g_eli_create (struct gctl_req*,struct g_class*,struct g_provider*,struct g_eli_metadata*,struct g_eli_metadata*,int) ; 
 scalar_t__ g_eli_keylen (scalar_t__,int) ; 
 scalar_t__ g_eli_str2aalgo (char const*) ; 
 void* g_eli_str2ealgo (char const*) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 void* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_eli_ctl_onetime(struct gctl_req *req, struct g_class *mp)
{
	struct g_eli_metadata md;
	struct g_provider *pp;
	const char *name;
	intmax_t *keylen, *sectorsize;
	u_char mkey[G_ELI_DATAIVKEYLEN];
	int *nargs, *detach, *noautoresize, *notrim;

	g_topology_assert();
	bzero(&md, sizeof(md));

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument.", "nargs");
		return;
	}
	if (*nargs != 1) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}

	strlcpy(md.md_magic, G_ELI_MAGIC, sizeof(md.md_magic));
	md.md_version = G_ELI_VERSION;
	md.md_flags |= G_ELI_FLAG_ONETIME;
	md.md_flags |= G_ELI_FLAG_AUTORESIZE;

	detach = gctl_get_paraml(req, "detach", sizeof(*detach));
	if (detach != NULL && *detach)
		md.md_flags |= G_ELI_FLAG_WO_DETACH;
	noautoresize = gctl_get_paraml(req, "noautoresize",
	    sizeof(*noautoresize));
	if (noautoresize != NULL && *noautoresize)
		md.md_flags &= ~G_ELI_FLAG_AUTORESIZE;
	notrim = gctl_get_paraml(req, "notrim", sizeof(*notrim));
	if (notrim != NULL && *notrim)
		md.md_flags |= G_ELI_FLAG_NODELETE;

	md.md_ealgo = CRYPTO_ALGORITHM_MIN - 1;
	name = gctl_get_asciiparam(req, "aalgo");
	if (name == NULL) {
		gctl_error(req, "No '%s' argument.", "aalgo");
		return;
	}
	if (*name != '\0') {
		md.md_aalgo = g_eli_str2aalgo(name);
		if (md.md_aalgo >= CRYPTO_ALGORITHM_MIN &&
		    md.md_aalgo <= CRYPTO_ALGORITHM_MAX) {
			md.md_flags |= G_ELI_FLAG_AUTH;
		} else {
			/*
			 * For backward compatibility, check if the -a option
			 * was used to provide encryption algorithm.
			 */
			md.md_ealgo = g_eli_str2ealgo(name);
			if (md.md_ealgo < CRYPTO_ALGORITHM_MIN ||
			    md.md_ealgo > CRYPTO_ALGORITHM_MAX) {
				gctl_error(req,
				    "Invalid authentication algorithm.");
				return;
			} else {
				gctl_error(req, "warning: The -e option, not "
				    "the -a option is now used to specify "
				    "encryption algorithm to use.");
			}
		}
	}

	if (md.md_ealgo < CRYPTO_ALGORITHM_MIN ||
	    md.md_ealgo > CRYPTO_ALGORITHM_MAX) {
		name = gctl_get_asciiparam(req, "ealgo");
		if (name == NULL) {
			gctl_error(req, "No '%s' argument.", "ealgo");
			return;
		}
		md.md_ealgo = g_eli_str2ealgo(name);
		if (md.md_ealgo < CRYPTO_ALGORITHM_MIN ||
		    md.md_ealgo > CRYPTO_ALGORITHM_MAX) {
			gctl_error(req, "Invalid encryption algorithm.");
			return;
		}
	}

	keylen = gctl_get_paraml(req, "keylen", sizeof(*keylen));
	if (keylen == NULL) {
		gctl_error(req, "No '%s' argument.", "keylen");
		return;
	}
	md.md_keylen = g_eli_keylen(md.md_ealgo, *keylen);
	if (md.md_keylen == 0) {
		gctl_error(req, "Invalid '%s' argument.", "keylen");
		return;
	}

	/* Not important here. */
	md.md_provsize = 0;
	/* Not important here. */
	bzero(md.md_salt, sizeof(md.md_salt));

	md.md_keys = 0x01;
	arc4rand(mkey, sizeof(mkey), 0);

	/* Not important here. */
	bzero(md.md_hash, sizeof(md.md_hash));

	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 0);
		return;
	}
	if (strncmp(name, "/dev/", strlen("/dev/")) == 0)
		name += strlen("/dev/");
	pp = g_provider_by_name(name);
	if (pp == NULL) {
		gctl_error(req, "Provider %s is invalid.", name);
		return;
	}

	sectorsize = gctl_get_paraml(req, "sectorsize", sizeof(*sectorsize));
	if (sectorsize == NULL) {
		gctl_error(req, "No '%s' argument.", "sectorsize");
		return;
	}
	if (*sectorsize == 0)
		md.md_sectorsize = pp->sectorsize;
	else {
		if (*sectorsize < 0 || (*sectorsize % pp->sectorsize) != 0) {
			gctl_error(req, "Invalid sector size.");
			return;
		}
		if (*sectorsize > PAGE_SIZE) {
			gctl_error(req, "warning: Using sectorsize bigger than "
			    "the page size!");
		}
		md.md_sectorsize = *sectorsize;
	}

	g_eli_create(req, mp, pp, &md, mkey, -1);
	explicit_bzero(mkey, sizeof(mkey));
	explicit_bzero(&md, sizeof(md));
}