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
struct gctl_req {int dummy; } ;
struct g_eli_metadata {unsigned char* md_mkeys; int md_keys; } ;
typedef  int /*<<< orphan*/  md ;
typedef  int intmax_t ;

/* Variables and functions */
 unsigned int G_ELI_MAXMKEYS ; 
 unsigned int G_ELI_MKEYLEN ; 
 int /*<<< orphan*/  arc4random_buf (unsigned char*,unsigned int) ; 
 int eli_metadata_read (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  eli_metadata_store (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  explicit_bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int gctl_get_intmax (struct gctl_req*,char*) ; 

__attribute__((used)) static void
eli_delkey_detached(struct gctl_req *req, const char *prov)
{
	struct g_eli_metadata md;
	unsigned char *mkeydst;
	unsigned int nkey;
	intmax_t val;
	bool all, force;

	if (eli_metadata_read(req, prov, &md) == -1)
		return;

	all = gctl_get_int(req, "all");
	if (all)
		arc4random_buf(md.md_mkeys, sizeof(md.md_mkeys));
	else {
		force = gctl_get_int(req, "force");
		val = gctl_get_intmax(req, "keyno");
		if (val == -1) {
			gctl_error(req, "Key number has to be specified.");
			return;
		}
		nkey = val;
		if (nkey >= G_ELI_MAXMKEYS) {
			gctl_error(req, "Invalid '%s' argument.", "keyno");
			return;
		}
		if (!(md.md_keys & (1 << nkey)) && !force) {
			gctl_error(req, "Master Key %u is not set.", nkey);
			return;
		}
		md.md_keys &= ~(1 << nkey);
		if (md.md_keys == 0 && !force) {
			gctl_error(req, "This is the last Master Key. Use '-f' "
			    "option if you really want to remove it.");
			return;
		}
		mkeydst = md.md_mkeys + nkey * G_ELI_MKEYLEN;
		arc4random_buf(mkeydst, G_ELI_MKEYLEN);
	}

	eli_metadata_store(req, prov, &md);
	explicit_bzero(&md, sizeof(md));
}