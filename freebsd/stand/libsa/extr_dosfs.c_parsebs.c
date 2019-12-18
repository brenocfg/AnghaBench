#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_7__ {int media; int spc; int fats; int /*<<< orphan*/  lsecs; int /*<<< orphan*/  secs; int /*<<< orphan*/  ressec; int /*<<< orphan*/  rdcl; int /*<<< orphan*/  lspf; int /*<<< orphan*/  dirents; int /*<<< orphan*/  spf; int /*<<< orphan*/  secsiz; } ;
struct TYPE_9__ {int* jmp; TYPE_1__ bpb; } ;
struct TYPE_8__ {int spc; int bsize; int spf; scalar_t__ rdcl; int lsnfat; int lsndir; int lsndta; scalar_t__ xclus; int fatsz; scalar_t__ dirents; scalar_t__ bshift; } ;
typedef  TYPE_2__ DOS_FS ;
typedef  TYPE_3__ DOS_BS ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LOCLUS ; 
 scalar_t__ SECSIZ ; 
 scalar_t__ cv2 (int /*<<< orphan*/ ) ; 
 scalar_t__ cv4 (int /*<<< orphan*/ ) ; 
 int entsec (scalar_t__) ; 
 scalar_t__ ffs (int) ; 
 scalar_t__ secblk (TYPE_2__*,int) ; 
 int secbyt (int) ; 

__attribute__((used)) static int
parsebs(DOS_FS *fs, DOS_BS *bs)
{
    u_int sc;

    if ((bs->jmp[0] != 0x69 &&
         bs->jmp[0] != 0xe9 &&
         (bs->jmp[0] != 0xeb || bs->jmp[2] != 0x90)) ||
        bs->bpb.media < 0xf0)
        return (EINVAL);
    if (cv2(bs->bpb.secsiz) != SECSIZ)
        return (EINVAL);
    if (!(fs->spc = bs->bpb.spc) || fs->spc & (fs->spc - 1))
        return (EINVAL);
    fs->bsize = secbyt(fs->spc);
    fs->bshift = ffs(fs->bsize) - 1;
    if ((fs->spf = cv2(bs->bpb.spf))) {
        if (bs->bpb.fats != 2)
            return (EINVAL);
        if (!(fs->dirents = cv2(bs->bpb.dirents)))
            return (EINVAL);
    } else {
        if (!(fs->spf = cv4(bs->bpb.lspf)))
            return (EINVAL);
        if (!bs->bpb.fats || bs->bpb.fats > 16)
            return (EINVAL);
        if ((fs->rdcl = cv4(bs->bpb.rdcl)) < LOCLUS)
            return (EINVAL);
    }
    if (!(fs->lsnfat = cv2(bs->bpb.ressec)))
        return (EINVAL);
    fs->lsndir = fs->lsnfat + fs->spf * bs->bpb.fats;
    fs->lsndta = fs->lsndir + entsec(fs->dirents);
    if (!(sc = cv2(bs->bpb.secs)) && !(sc = cv4(bs->bpb.lsecs)))
        return (EINVAL);
    if (fs->lsndta > sc)
        return (EINVAL);
    if ((fs->xclus = secblk(fs, sc - fs->lsndta) + 1) < LOCLUS)
        return (EINVAL);
    fs->fatsz = fs->dirents ? fs->xclus < 0xff6 ? 12 : 16 : 32;
    sc = (secbyt(fs->spf) << 1) / (fs->fatsz >> 2) - 1;
    if (fs->xclus > sc)
        fs->xclus = sc;
    return (0);
}