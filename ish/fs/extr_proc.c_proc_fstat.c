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
struct statbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct fd {TYPE_1__ proc; } ;

/* Variables and functions */
 int proc_entry_stat (int /*<<< orphan*/ *,struct statbuf*) ; 

__attribute__((used)) static int proc_fstat(struct fd *fd, struct statbuf *stat) {
    return proc_entry_stat(&fd->proc.entry, stat);
}