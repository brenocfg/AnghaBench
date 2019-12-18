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
struct bpf_prog {int /*<<< orphan*/  bpf_func; scalar_t__ jited; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_unlock_free (struct bpf_prog*) ; 
 int /*<<< orphan*/  module_memfree (int /*<<< orphan*/ ) ; 

void bpf_jit_free(struct bpf_prog *fp)
{
	if (fp->jited)
		module_memfree(fp->bpf_func);

	bpf_prog_unlock_free(fp);
}