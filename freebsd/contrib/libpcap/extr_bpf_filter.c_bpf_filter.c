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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_filter_with_aux_data (struct bpf_insn const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u_int
bpf_filter(const struct bpf_insn *pc, const u_char *p, u_int wirelen,
    u_int buflen)
{
	return bpf_filter_with_aux_data(pc, p, wirelen, buflen, NULL);
}