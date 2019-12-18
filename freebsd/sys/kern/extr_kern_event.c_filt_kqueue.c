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
struct kqueue {int /*<<< orphan*/  kq_count; } ;
struct knote {int /*<<< orphan*/  kn_data; TYPE_1__* kn_fp; } ;
struct TYPE_2__ {struct kqueue* f_data; } ;

/* Variables and functions */

__attribute__((used)) static int
filt_kqueue(struct knote *kn, long hint)
{
	struct kqueue *kq = kn->kn_fp->f_data;

	kn->kn_data = kq->kq_count;
	return (kn->kn_data > 0);
}