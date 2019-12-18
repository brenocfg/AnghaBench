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
struct hashfile {unsigned int offset; int /*<<< orphan*/  buffer; int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  flush (struct hashfile*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* the_hash_algo ; 

void hashflush(struct hashfile *f)
{
	unsigned offset = f->offset;

	if (offset) {
		the_hash_algo->update_fn(&f->ctx, f->buffer, offset);
		flush(f, f->buffer, offset);
		f->offset = 0;
	}
}