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
struct ib_uverbs_event_file {int /*<<< orphan*/  ref; scalar_t__ is_async; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_2__ {struct ib_uverbs_event_file* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_event_fops ; 

struct ib_uverbs_event_file *ib_uverbs_lookup_comp_file(int fd)
{
	struct ib_uverbs_event_file *ev_file = NULL;
	struct fd f = fdget(fd);

	if (!f.file)
		return NULL;

	if (f.file->f_op != &uverbs_event_fops)
		goto out;

	ev_file = f.file->private_data;
	if (ev_file->is_async) {
		ev_file = NULL;
		goto out;
	}

	kref_get(&ev_file->ref);

out:
	fdput(f);
	return ev_file;
}