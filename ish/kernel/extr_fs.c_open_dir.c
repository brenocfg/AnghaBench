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
struct statbuf {int mode; } ;
struct fd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_PWD ; 
 struct fd* ERR_PTR (int) ; 
 int /*<<< orphan*/  O_RDONLY_ ; 
 int S_IFDIR ; 
 int _ENOTDIR ; 
 struct fd* generic_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int generic_statat (int /*<<< orphan*/ ,char const*,struct statbuf*,int) ; 

__attribute__((used)) static struct fd *open_dir(const char *path) {
    struct statbuf stat;
    int err = generic_statat(AT_PWD, path, &stat, true);
    if (err < 0)
        return ERR_PTR(err);
    if (!(stat.mode & S_IFDIR))
        return ERR_PTR(_ENOTDIR);

    return generic_open(path, O_RDONLY_, 0);
}