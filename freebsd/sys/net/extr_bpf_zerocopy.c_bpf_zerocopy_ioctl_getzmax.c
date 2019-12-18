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
struct thread {int dummy; } ;
struct bpf_d {scalar_t__ bd_bufmode; } ;

/* Variables and functions */
 scalar_t__ BPF_BUFMODE_ZBUF ; 
 size_t BPF_MAX_PAGES ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t PAGE_SIZE ; 

int
bpf_zerocopy_ioctl_getzmax(struct thread *td, struct bpf_d *d, size_t *i)
{

	KASSERT(d->bd_bufmode == BPF_BUFMODE_ZBUF,
	    ("bpf_zerocopy_ioctl_getzmax: not in zbuf mode"));

	*i = BPF_MAX_PAGES * PAGE_SIZE;
	return (0);
}