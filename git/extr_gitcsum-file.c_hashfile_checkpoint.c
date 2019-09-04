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
struct hashfile_checkpoint {int /*<<< orphan*/  ctx; int /*<<< orphan*/  offset; } ;
struct hashfile {int /*<<< orphan*/  ctx; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashflush (struct hashfile*) ; 

void hashfile_checkpoint(struct hashfile *f, struct hashfile_checkpoint *checkpoint)
{
	hashflush(f);
	checkpoint->offset = f->total;
	checkpoint->ctx = f->ctx;
}