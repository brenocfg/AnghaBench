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
struct fdtable {struct fd** files; } ;
struct fd {int dummy; } ;
typedef  size_t fd_t ;
struct TYPE_4__ {TYPE_1__* files; } ;
struct TYPE_3__ {unsigned int size; } ;

/* Variables and functions */
 TYPE_2__* current ; 

struct fd *fdtable_get(struct fdtable *table, fd_t f) {
    if (f < 0 || (unsigned) f >= current->files->size)
        return NULL;
    return table->files[f];
}