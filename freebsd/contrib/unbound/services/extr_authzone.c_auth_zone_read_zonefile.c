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
typedef  int /*<<< orphan*/  uint8_t ;
struct sldns_file_parse_state {int default_ttl; int origin_len; int /*<<< orphan*/  origin; } ;
struct config_file {scalar_t__* chrootdir; } ;
struct auth_zone {scalar_t__* zonefile; int namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  data; scalar_t__ zone_is_slave; } ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  rr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int LDNS_RR_BUF_SIZE ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  auth_data_cmp ; 
 int /*<<< orphan*/  auth_data_del ; 
 int /*<<< orphan*/  az_parse_file (struct auth_zone*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct sldns_file_parse_state*,char*,int /*<<< orphan*/ ,struct config_file*) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (char*,char*,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sldns_file_parse_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* sldns_wire2str_dname (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 scalar_t__ strncmp (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*,char*) ; 
 scalar_t__ verbosity ; 

int
auth_zone_read_zonefile(struct auth_zone* z, struct config_file* cfg)
{
	uint8_t rr[LDNS_RR_BUF_SIZE];
	struct sldns_file_parse_state state;
	char* zfilename;
	FILE* in;
	if(!z || !z->zonefile || z->zonefile[0]==0)
		return 1; /* no file, or "", nothing to read */
	
	zfilename = z->zonefile;
	if(cfg->chrootdir && cfg->chrootdir[0] && strncmp(zfilename,
		cfg->chrootdir, strlen(cfg->chrootdir)) == 0)
		zfilename += strlen(cfg->chrootdir);
	if(verbosity >= VERB_ALGO) {
		char nm[255+1];
		dname_str(z->name, nm);
		verbose(VERB_ALGO, "read zonefile %s for %s", zfilename, nm);
	}
	in = fopen(zfilename, "r");
	if(!in) {
		char* n = sldns_wire2str_dname(z->name, z->namelen);
		if(z->zone_is_slave && errno == ENOENT) {
			/* we fetch the zone contents later, no file yet */
			verbose(VERB_ALGO, "no zonefile %s for %s",
				zfilename, n?n:"error");
			free(n);
			return 1;
		}
		log_err("cannot open zonefile %s for %s: %s",
			zfilename, n?n:"error", strerror(errno));
		free(n);
		return 0;
	}

	/* clear the data tree */
	traverse_postorder(&z->data, auth_data_del, NULL);
	rbtree_init(&z->data, &auth_data_cmp);

	memset(&state, 0, sizeof(state));
	/* default TTL to 3600 */
	state.default_ttl = 3600;
	/* set $ORIGIN to the zone name */
	if(z->namelen <= sizeof(state.origin)) {
		memcpy(state.origin, z->name, z->namelen);
		state.origin_len = z->namelen;
	}
	/* parse the (toplevel) file */
	if(!az_parse_file(z, in, rr, sizeof(rr), &state, zfilename, 0, cfg)) {
		char* n = sldns_wire2str_dname(z->name, z->namelen);
		log_err("error parsing zonefile %s for %s",
			zfilename, n?n:"error");
		free(n);
		fclose(in);
		return 0;
	}
	fclose(in);
	return 1;
}