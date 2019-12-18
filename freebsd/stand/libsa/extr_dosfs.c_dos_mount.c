#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct open_file {int dummy; } ;
struct TYPE_8__ {int* h_clus; } ;
struct TYPE_10__ {char* name; int* clus; TYPE_1__ dex; } ;
struct TYPE_9__ {int fatsz; int rdcl; TYPE_4__ root; int /*<<< orphan*/ * fatbuf; struct open_file* fd; } ;
typedef  TYPE_2__ DOS_FS ;
typedef  int /*<<< orphan*/  DOS_BS ;

/* Variables and functions */
 int /*<<< orphan*/  FATBLKSZ ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int dos_read_fatblk (TYPE_2__*,struct open_file*,int /*<<< orphan*/ ) ; 
 TYPE_4__* dot ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int ioget (struct open_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int parsebs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secbyt (int) ; 

__attribute__((used)) static int
dos_mount(DOS_FS *fs, struct open_file *fd)
{
    int err;
    u_char *buf;

    bzero(fs, sizeof(DOS_FS));
    fs->fd = fd;

    if ((buf = malloc(secbyt(1))) == NULL)
        return (errno);
    if ((err = ioget(fs->fd, 0, buf, secbyt(1))) ||
        (err = parsebs(fs, (DOS_BS *)buf))) {
        free(buf);
        return (err);
    }
    free(buf);

    if ((fs->fatbuf = malloc(FATBLKSZ)) == NULL)
        return (errno);
    err = dos_read_fatblk(fs, fd, 0);
    if (err != 0) {
        free(fs->fatbuf);
        return (err);
    }

    fs->root = dot[0];
    fs->root.name[0] = ' ';
    if (fs->fatsz == 32) {
        fs->root.clus[0] = fs->rdcl & 0xff;
        fs->root.clus[1] = (fs->rdcl >> 8) & 0xff;
        fs->root.dex.h_clus[0] = (fs->rdcl >> 16) & 0xff;
        fs->root.dex.h_clus[1] = (fs->rdcl >> 24) & 0xff;
    }
    return (0);
}