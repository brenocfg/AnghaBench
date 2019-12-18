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
struct entry {int e_flags; } ;
struct direct {int d_type; int /*<<< orphan*/  d_ino; int /*<<< orphan*/  d_name; } ;
struct afile {char* fname; int len; char prefix; char postfix; int /*<<< orphan*/  fnum; } ;

/* Variables and functions */
#define  DT_BLK 136 
#define  DT_CHR 135 
#define  DT_DIR 134 
#define  DT_FIFO 133 
#define  DT_LNK 132 
#define  DT_REG 131 
#define  DT_SOCK 130 
#define  DT_UNKNOWN 129 
#define  DT_WHT 128 
 int NEW ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ TSTINO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  inodetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 struct entry* lookupname (char*) ; 
 char* savename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vflag ; 

__attribute__((used)) static void
mkentry(char *name, struct direct *dp, struct afile *fp)
{
	char *cp;
	struct entry *np;

	fp->fnum = dp->d_ino;
	fp->fname = savename(dp->d_name);
	for (cp = fp->fname; *cp; cp++)
		if (!vflag && !isprint((unsigned char)*cp))
			*cp = '?';
	fp->len = cp - fp->fname;
	if (dflag && TSTINO(fp->fnum, dumpmap) == 0)
		fp->prefix = '^';
	else if ((np = lookupname(name)) != NULL && (np->e_flags & NEW))
		fp->prefix = '*';
	else
		fp->prefix = ' ';
	switch(dp->d_type) {

	default:
		fprintf(stderr, "Warning: undefined file type %d\n",
		    dp->d_type);
		/* FALLTHROUGH */
	case DT_REG:
		fp->postfix = ' ';
		break;

	case DT_LNK:
		fp->postfix = '@';
		break;

	case DT_FIFO:
	case DT_SOCK:
		fp->postfix = '=';
		break;

	case DT_CHR:
	case DT_BLK:
		fp->postfix = '#';
		break;

	case DT_WHT:
		fp->postfix = '%';
		break;

	case DT_UNKNOWN:
	case DT_DIR:
		if (inodetype(dp->d_ino) == NODE)
			fp->postfix = '/';
		else
			fp->postfix = ' ';
		break;
	}
	return;
}