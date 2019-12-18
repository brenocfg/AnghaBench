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
typedef  int /*<<< orphan*/  fd_t ;
struct TYPE_4__ {TYPE_1__* files; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 struct fd* fdtable_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

struct fd *f_get(fd_t f) {
    lock(&current->files->lock);
    struct fd *fd = fdtable_get(current->files, f);
    unlock(&current->files->lock);
    return fd;
}