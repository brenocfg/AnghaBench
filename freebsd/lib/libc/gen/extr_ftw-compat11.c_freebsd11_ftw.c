#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fts_info; char const* fts_path; struct freebsd11_stat const* fts_statp; } ;
typedef  TYPE_1__ FTSENT11 ;
typedef  int /*<<< orphan*/  FTS11 ;

/* Variables and functions */
 int EINVAL ; 
 int ELOOP ; 
 int FTS_COMFOLLOW ; 
#define  FTS_D 137 
#define  FTS_DC 136 
#define  FTS_DEFAULT 135 
#define  FTS_DNR 134 
#define  FTS_DP 133 
#define  FTS_F 132 
 int FTS_LOGICAL ; 
 int FTS_NOCHDIR ; 
#define  FTS_NS 131 
#define  FTS_NSOK 130 
#define  FTS_SL 129 
#define  FTS_SLNONE 128 
 int FTW_D ; 
 int FTW_DNR ; 
 int FTW_F ; 
 int FTW_NS ; 
 int FTW_SL ; 
 int errno ; 
 scalar_t__ freebsd11_fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freebsd11_fts_open (char* const*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* freebsd11_fts_read (int /*<<< orphan*/ *) ; 

int
freebsd11_ftw(const char *path,
    int (*fn)(const char *, const struct freebsd11_stat *, int), int nfds)
{
	char * const paths[2] = { (char *)path, NULL };
	FTSENT11 *cur;
	FTS11 *ftsp;
	int error = 0, fnflag, sverrno;

	/* XXX - nfds is currently unused */
	if (nfds < 1) {
		errno = EINVAL;
		return (-1);
	}

	ftsp = freebsd11_fts_open(paths,
	    FTS_LOGICAL | FTS_COMFOLLOW | FTS_NOCHDIR, NULL);
	if (ftsp == NULL)
		return (-1);
	while ((cur = freebsd11_fts_read(ftsp)) != NULL) {
		switch (cur->fts_info) {
		case FTS_D:
			fnflag = FTW_D;
			break;
		case FTS_DNR:
			fnflag = FTW_DNR;
			break;
		case FTS_DP:
			/* we only visit in preorder */
			continue;
		case FTS_F:
		case FTS_DEFAULT:
			fnflag = FTW_F;
			break;
		case FTS_NS:
		case FTS_NSOK:
		case FTS_SLNONE:
			fnflag = FTW_NS;
			break;
		case FTS_SL:
			fnflag = FTW_SL;
			break;
		case FTS_DC:
			errno = ELOOP;
			/* FALLTHROUGH */
		default:
			error = -1;
			goto done;
		}
		error = fn(cur->fts_path, cur->fts_statp, fnflag);
		if (error != 0)
			break;
	}
done:
	sverrno = errno;
	if (freebsd11_fts_close(ftsp) != 0 && error == 0)
		error = -1;
	else
		errno = sverrno;
	return (error);
}