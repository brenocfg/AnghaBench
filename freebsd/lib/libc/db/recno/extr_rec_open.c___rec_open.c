#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_24__ {int /*<<< orphan*/  lorder; int /*<<< orphan*/ * prefix; int /*<<< orphan*/ * compare; int /*<<< orphan*/  psize; scalar_t__ minkeypage; scalar_t__ maxkeypage; int /*<<< orphan*/  cachesize; scalar_t__ flags; } ;
struct TYPE_23__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  seq; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  fd; int /*<<< orphan*/  del; int /*<<< orphan*/  close; TYPE_2__* internal; } ;
struct TYPE_22__ {scalar_t__ bt_reclen; char bt_bval; int bt_rfd; scalar_t__ (* bt_irec ) (TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ bt_msize; scalar_t__ bt_smap; scalar_t__ bt_cmap; scalar_t__ bt_emap; int flags; int /*<<< orphan*/  bt_mp; int /*<<< orphan*/ * bt_rfp; } ;
struct TYPE_21__ {int flags; scalar_t__ reclen; char bval; int /*<<< orphan*/ * bfname; int /*<<< orphan*/  lorder; int /*<<< orphan*/  psize; int /*<<< orphan*/  cachesize; } ;
typedef  TYPE_1__ RECNOINFO ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ DB ;
typedef  TYPE_4__ BTREEINFO ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int EINVAL ; 
 int ESPIPE ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int) ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  MAX_REC_NUMBER ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int O_ACCMODE ; 
 int O_CLOEXEC ; 
#define  O_RDONLY 129 
#define  O_RDWR 128 
 int /*<<< orphan*/  PROT_READ ; 
 int P_BLEAF ; 
 int P_RLEAF ; 
 int /*<<< orphan*/  P_ROOT ; 
 int P_TYPE ; 
 scalar_t__ RET_ERROR ; 
 int R_CLOSEFP ; 
 int R_EOF ; 
 int R_FIXEDLEN ; 
 int R_FIXLEN ; 
 int R_INMEM ; 
 int R_MEMMAPPED ; 
 int R_NOKEY ; 
 int R_RDONLY ; 
 int R_RECNO ; 
 int R_SNAPSHOT ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  __bt_close (TYPE_3__*) ; 
 TYPE_3__* __bt_open (int /*<<< orphan*/ *,int,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  __rec_close ; 
 int /*<<< orphan*/  __rec_delete ; 
 int /*<<< orphan*/  __rec_fd ; 
 scalar_t__ __rec_fmap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __rec_fpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rec_get ; 
 int /*<<< orphan*/  __rec_put ; 
 int /*<<< orphan*/  __rec_seq ; 
 int /*<<< orphan*/  __rec_sync ; 
 scalar_t__ __rec_vmap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __rec_vpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _close (int) ; 
 scalar_t__ _fstat (int,struct stat*) ; 
 int _open (char const*,int,int) ; 
 int errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

DB *
__rec_open(const char *fname, int flags, int mode, const RECNOINFO *openinfo,
    int dflags)
{
	BTREE *t;
	BTREEINFO btopeninfo;
	DB *dbp;
	PAGE *h;
	struct stat sb;
	int rfd, sverrno;

	/* Open the user's file -- if this fails, we're done. */
	if (fname != NULL && (rfd = _open(fname, flags | O_CLOEXEC, mode)) < 0)
		return (NULL);

	/* Create a btree in memory (backed by disk). */
	dbp = NULL;
	if (openinfo) {
		if (openinfo->flags & ~(R_FIXEDLEN | R_NOKEY | R_SNAPSHOT))
			goto einval;
		btopeninfo.flags = 0;
		btopeninfo.cachesize = openinfo->cachesize;
		btopeninfo.maxkeypage = 0;
		btopeninfo.minkeypage = 0;
		btopeninfo.psize = openinfo->psize;
		btopeninfo.compare = NULL;
		btopeninfo.prefix = NULL;
		btopeninfo.lorder = openinfo->lorder;
		dbp = __bt_open(openinfo->bfname,
		    O_RDWR, S_IRUSR | S_IWUSR, &btopeninfo, dflags);
	} else
		dbp = __bt_open(NULL, O_RDWR, S_IRUSR | S_IWUSR, NULL, dflags);
	if (dbp == NULL)
		goto err;

	/*
	 * Some fields in the tree structure are recno specific.  Fill them
	 * in and make the btree structure look like a recno structure.  We
	 * don't change the bt_ovflsize value, it's close enough and slightly
	 * bigger.
	 */
	t = dbp->internal;
	if (openinfo) {
		if (openinfo->flags & R_FIXEDLEN) {
			F_SET(t, R_FIXLEN);
			t->bt_reclen = openinfo->reclen;
			if (t->bt_reclen == 0)
				goto einval;
		}
		t->bt_bval = openinfo->bval;
	} else
		t->bt_bval = '\n';

	F_SET(t, R_RECNO);
	if (fname == NULL)
		F_SET(t, R_EOF | R_INMEM);
	else
		t->bt_rfd = rfd;

	if (fname != NULL) {
		/*
		 * In 4.4BSD, stat(2) returns true for ISSOCK on pipes.
		 * Unfortunately, that's not portable, so we use lseek
		 * and check the errno values.
		 */
		errno = 0;
		if (lseek(rfd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE) {
			switch (flags & O_ACCMODE) {
			case O_RDONLY:
				F_SET(t, R_RDONLY);
				break;
			default:
				goto einval;
			}
slow:			if ((t->bt_rfp = fdopen(rfd, "r")) == NULL)
				goto err;
			F_SET(t, R_CLOSEFP);
			t->bt_irec =
			    F_ISSET(t, R_FIXLEN) ? __rec_fpipe : __rec_vpipe;
		} else {
			switch (flags & O_ACCMODE) {
			case O_RDONLY:
				F_SET(t, R_RDONLY);
				break;
			case O_RDWR:
				break;
			default:
				goto einval;
			}

			if (_fstat(rfd, &sb))
				goto err;
			/*
			 * Kluge -- we'd like to test to see if the file is too
			 * big to mmap.  Since, we don't know what size or type
			 * off_t's or size_t's are, what the largest unsigned
			 * integral type is, or what random insanity the local
			 * C compiler will perpetrate, doing the comparison in
			 * a portable way is flatly impossible.  Hope that mmap
			 * fails if the file is too large.
			 */
			if (sb.st_size == 0)
				F_SET(t, R_EOF);
			else {
#ifdef MMAP_NOT_AVAILABLE
				/*
				 * XXX
				 * Mmap doesn't work correctly on many current
				 * systems.  In particular, it can fail subtly,
				 * with cache coherency problems.  Don't use it
				 * for now.
				 */
				t->bt_msize = sb.st_size;
				if ((t->bt_smap = mmap(NULL, t->bt_msize,
				    PROT_READ, MAP_PRIVATE, rfd,
				    (off_t)0)) == MAP_FAILED)
					goto slow;
				t->bt_cmap = t->bt_smap;
				t->bt_emap = t->bt_smap + sb.st_size;
				t->bt_irec = F_ISSET(t, R_FIXLEN) ?
				    __rec_fmap : __rec_vmap;
				F_SET(t, R_MEMMAPPED);
#else
				goto slow;
#endif
			}
		}
	}

	/* Use the recno routines. */
	dbp->close = __rec_close;
	dbp->del = __rec_delete;
	dbp->fd = __rec_fd;
	dbp->get = __rec_get;
	dbp->put = __rec_put;
	dbp->seq = __rec_seq;
	dbp->sync = __rec_sync;

	/* If the root page was created, reset the flags. */
	if ((h = mpool_get(t->bt_mp, P_ROOT, 0)) == NULL)
		goto err;
	if ((h->flags & P_TYPE) == P_BLEAF) {
		F_CLR(h, P_TYPE);
		F_SET(h, P_RLEAF);
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	} else
		mpool_put(t->bt_mp, h, 0);

	if (openinfo && openinfo->flags & R_SNAPSHOT &&
	    !F_ISSET(t, R_EOF | R_INMEM) &&
	    t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
		goto err;
	return (dbp);

einval:	errno = EINVAL;
err:	sverrno = errno;
	if (dbp != NULL)
		(void)__bt_close(dbp);
	if (fname != NULL)
		(void)_close(rfd);
	errno = sverrno;
	return (NULL);
}