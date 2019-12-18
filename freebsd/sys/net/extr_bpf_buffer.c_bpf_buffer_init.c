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
struct bpf_d {int /*<<< orphan*/  bd_bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_bufsize ; 

void
bpf_buffer_init(struct bpf_d *d)
{

	d->bd_bufsize = bpf_bufsize;
}