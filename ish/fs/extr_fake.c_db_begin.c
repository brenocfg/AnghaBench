#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  begin; } ;
struct mount {TYPE_1__ stmt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_exec_reset (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 

void db_begin(struct mount *mount) {
    lock(&mount->lock);
    db_exec_reset(mount, mount->stmt.begin);
}