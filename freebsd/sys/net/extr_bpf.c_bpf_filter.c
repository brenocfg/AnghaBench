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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */

u_int
bpf_filter(const struct bpf_insn *pc, u_char *p, u_int wirelen, u_int buflen)
{
	return -1;	/* "no filter" behaviour */
}