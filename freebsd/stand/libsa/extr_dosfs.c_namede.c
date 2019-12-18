#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  fatsz; TYPE_2__ root; } ;
typedef  TYPE_1__ DOS_FS ;
typedef  TYPE_2__ DOS_DE ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOTDIR ; 
 int FA_DIR ; 
 int lookup (TYPE_1__*,int /*<<< orphan*/ ,char*,TYPE_2__**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  stclus (int /*<<< orphan*/ ,TYPE_2__*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
namede(DOS_FS *fs, const char *path, DOS_DE **dep)
{
    char name[256];
    DOS_DE *de;
    char *s;
    size_t n;
    int err;

    err = 0;
    de = &fs->root;
    while (*path) {
        while (*path == '/')
            path++;
        if (*path == '\0')
            break;
        if (!(s = strchr(path, '/')))
            s = strchr(path, 0);
        if ((n = s - path) > 255)
            return (ENAMETOOLONG);
        memcpy(name, path, n);
        name[n] = 0;
        path = s;
        if (!(de->attr & FA_DIR))
            return (ENOTDIR);
        if ((err = lookup(fs, stclus(fs->fatsz, de), name, &de)))
            return (err);
    }
    *dep = de;
    return (0);
}