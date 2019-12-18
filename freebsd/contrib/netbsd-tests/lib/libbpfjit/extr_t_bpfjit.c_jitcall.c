#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int (* bpfjit_func_t ) (int /*<<< orphan*/ *,TYPE_1__*) ;
struct TYPE_4__ {unsigned int wirelen; unsigned int buflen; int /*<<< orphan*/  const* pkt; } ;
typedef  TYPE_1__ bpf_args_t ;

/* Variables and functions */

__attribute__((used)) static inline
unsigned int jitcall(bpfjit_func_t fn,
    const uint8_t *pkt, unsigned int wirelen, unsigned int buflen)
{
	bpf_args_t args;

	args.pkt = pkt;
	args.wirelen = wirelen;
	args.buflen = buflen;

	return fn(NULL, &args);
}