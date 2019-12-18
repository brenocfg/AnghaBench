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
struct fd {int dummy; } ;
struct TYPE_4__ {TYPE_1__* fs; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct fd* pwd; struct fd* root; } ;

/* Variables and functions */
 struct fd* AT_PWD ; 
 int MAX_PATH ; 
 int _ENOENT ; 
 int __path_normalize (char*,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int generic_getpath (struct fd*,char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_is_normalized (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int path_normalize(struct fd *at, const char *path, char *out, int flags) {
    assert(at != NULL);
    if (strcmp(path, "") == 0)
        return _ENOENT;

    // start with root or cwd, depending on whether it starts with a slash
    lock(&current->fs->lock);
    if (path[0] == '/')
        at = current->fs->root;
    else if (at == AT_PWD)
        at = current->fs->pwd;
    unlock(&current->fs->lock);
    char at_path[MAX_PATH];
    if (at != NULL) {
        int err = generic_getpath(at, at_path);
        if (err < 0)
            return err;
        assert(path_is_normalized(at_path));
    }

    return __path_normalize(at != NULL ? at_path : NULL, path, out, flags, 0);
}