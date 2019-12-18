#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct open_file {void* f_fsdata; } ;
struct TYPE_14__ {int attr; int /*<<< orphan*/  size; } ;
struct TYPE_13__ {TYPE_3__ de; TYPE_1__* fs; } ;
struct TYPE_12__ {int /*<<< orphan*/  links; int /*<<< orphan*/  fatsz; } ;
typedef  TYPE_1__ DOS_FS ;
typedef  TYPE_2__ DOS_FILE ;
typedef  TYPE_3__ DOS_DE ;

/* Variables and functions */
 int EINVAL ; 
 int FA_DIR ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 scalar_t__ cv4 (int /*<<< orphan*/ ) ; 
 int dos_mount (TYPE_1__*,struct open_file*) ; 
 int /*<<< orphan*/  dos_unmount (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* malloc (int) ; 
 int namede (TYPE_1__*,char const*,TYPE_3__**) ; 
 int /*<<< orphan*/  okclus (TYPE_1__*,scalar_t__) ; 
 scalar_t__ stclus (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int
dos_open(const char *path, struct open_file *fd)
{
    DOS_DE *de;
    DOS_FILE *f;
    DOS_FS *fs;
    u_int size, clus;
    int err;

    /* Allocate mount structure, associate with open */
    if ((fs = malloc(sizeof(DOS_FS))) == NULL)
        return (errno);
    if ((err = dos_mount(fs, fd))) {
        free(fs);
        return (err);
    }

    if ((err = namede(fs, path, &de))) {
        dos_unmount(fs);
        return (err);
    }

    clus = stclus(fs->fatsz, de);
    size = cv4(de->size);

    if ((!(de->attr & FA_DIR) && (!clus != !size)) ||
	((de->attr & FA_DIR) && size) ||
	(clus && !okclus(fs, clus))) {
        dos_unmount(fs);
        return (EINVAL);
    }
    if ((f = malloc(sizeof(DOS_FILE))) == NULL) {
        err = errno;
        dos_unmount(fs);
        return (err);
    }
    bzero(f, sizeof(DOS_FILE));
    f->fs = fs;
    fs->links++;
    f->de = *de;
    fd->f_fsdata = (void *)f;
    return (0);
}