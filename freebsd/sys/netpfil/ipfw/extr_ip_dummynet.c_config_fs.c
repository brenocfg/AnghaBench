#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dn_schk {int /*<<< orphan*/ * siht; } ;
struct dn_id {int dummy; } ;
struct TYPE_3__ {int len; } ;
struct dn_fs {int fs_nr; int flags; int qsize; int buckets; int* par; int /*<<< orphan*/  sched_nr; TYPE_1__ oid; } ;
struct dn_fsk {int /*<<< orphan*/ * aqmfp; struct dn_fs fs; scalar_t__ sched; } ;
struct dn_extra_parms {int dummy; } ;
struct TYPE_4__ {int hash_size; int fsk_count; int /*<<< orphan*/  id; int /*<<< orphan*/  fshash; int /*<<< orphan*/  max_hash_size; int /*<<< orphan*/  slot_limit; int /*<<< orphan*/  byte_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int) ; 
 int DNHT_INSERT ; 
 int /*<<< orphan*/  DN_BH_WLOCK () ; 
 int /*<<< orphan*/  DN_BH_WUNLOCK () ; 
 int DN_DESTROY ; 
 int DN_DETACH ; 
 int DN_HAVE_MASK ; 
 int DN_MAX_ID ; 
 int DN_QSIZE_BYTES ; 
 int /*<<< orphan*/  DX (int,char*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct dn_schk*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ND (char*,int) ; 
 scalar_t__ bcmp (struct dn_fs*,struct dn_fs*,int) ; 
 int /*<<< orphan*/  config_aqm (struct dn_fsk*,struct dn_extra_parms*,int) ; 
 TYPE_2__ dn_cfg ; 
 struct dn_fsk* dn_ht_find (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct dn_extra_parms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsk_attach (struct dn_fsk*,struct dn_schk*) ; 
 int /*<<< orphan*/  fsk_detach (struct dn_fsk*,int) ; 
 int /*<<< orphan*/  ipdn_bound_var (int*,int,int,int /*<<< orphan*/ ,char*) ; 
 struct dn_schk* locate_scheduler (int /*<<< orphan*/ ) ; 
 struct dn_extra_parms* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dn_extra_parms*,struct dn_id*,int) ; 

__attribute__((used)) static struct dn_fsk *
config_fs(struct dn_fs *nfs, struct dn_id *arg, int locked)
{
	int i;
	struct dn_fsk *fs;
#ifdef NEW_AQM
	struct dn_extra_parms *ep;
#endif

	if (nfs->oid.len != sizeof(*nfs)) {
		D("invalid flowset len %d", nfs->oid.len);
		return NULL;
	}
	i = nfs->fs_nr;
	if (i <= 0 || i >= 3*DN_MAX_ID)
		return NULL;
#ifdef NEW_AQM
	ep = NULL;
	if (arg != NULL) {
		ep = malloc(sizeof(*ep), M_TEMP, locked ? M_NOWAIT : M_WAITOK);
		if (ep == NULL)
			return (NULL);
		memcpy(ep, arg, sizeof(*ep));
	}
#endif
	ND("flowset %d", i);
	/* XXX other sanity checks */
        if (nfs->flags & DN_QSIZE_BYTES) {
		ipdn_bound_var(&nfs->qsize, 16384,
		    1500, dn_cfg.byte_limit, NULL); // "queue byte size");
        } else {
		ipdn_bound_var(&nfs->qsize, 50,
		    1, dn_cfg.slot_limit, NULL); // "queue slot size");
        }
	if (nfs->flags & DN_HAVE_MASK) {
		/* make sure we have some buckets */
		ipdn_bound_var((int *)&nfs->buckets, dn_cfg.hash_size,
			1, dn_cfg.max_hash_size, "flowset buckets");
	} else {
		nfs->buckets = 1;	/* we only need 1 */
	}
	if (!locked)
		DN_BH_WLOCK();
	do { /* exit with break when done */
	    struct dn_schk *s;
	    int flags = nfs->sched_nr ? DNHT_INSERT : 0;
	    int j;
	    int oldc = dn_cfg.fsk_count;
	    fs = dn_ht_find(dn_cfg.fshash, i, flags, NULL);
	    if (fs == NULL) {
		D("missing sched for flowset %d", i);
	        break;
	    }
	    /* grab some defaults from the existing one */
	    if (nfs->sched_nr == 0) /* reuse */
		nfs->sched_nr = fs->fs.sched_nr;
	    for (j = 0; j < sizeof(nfs->par)/sizeof(nfs->par[0]); j++) {
		if (nfs->par[j] == -1) /* reuse */
		    nfs->par[j] = fs->fs.par[j];
	    }
	    if (bcmp(&fs->fs, nfs, sizeof(*nfs)) == 0) {
		ND("flowset %d unchanged", i);
#ifdef NEW_AQM
		if (ep != NULL) {
			/*
			 * Reconfigure AQM as the parameters can be changed.
			 * We consider the flowset as busy if it has scheduler
			 * instance(s).
			 */ 
			s = locate_scheduler(nfs->sched_nr);
			config_aqm(fs, ep, s != NULL && s->siht != NULL);
		}
#endif
		break; /* no change, nothing to do */
	    }
	    if (oldc != dn_cfg.fsk_count)	/* new item */
		dn_cfg.id++;
	    s = locate_scheduler(nfs->sched_nr);
	    /* detach from old scheduler if needed, preserving
	     * queues if we need to reattach. Then update the
	     * configuration, and possibly attach to the new sched.
	     */
	    DX(2, "fs %d changed sched %d@%p to %d@%p",
		fs->fs.fs_nr,
		fs->fs.sched_nr, fs->sched, nfs->sched_nr, s);
	    if (fs->sched) {
		int flags = s ? DN_DETACH : (DN_DETACH | DN_DESTROY);
		flags |= DN_DESTROY; /* XXX temporary */
		fsk_detach(fs, flags);
	    }
	    fs->fs = *nfs; /* copy configuration */
#ifdef NEW_AQM
			fs->aqmfp = NULL;
			if (ep != NULL)
				config_aqm(fs, ep, s != NULL &&
				    s->siht != NULL);
#endif
	    if (s != NULL)
		fsk_attach(fs, s);
	} while (0);
	if (!locked)
		DN_BH_WUNLOCK();
#ifdef NEW_AQM
	if (ep != NULL)
		free(ep, M_TEMP);
#endif
	return fs;
}