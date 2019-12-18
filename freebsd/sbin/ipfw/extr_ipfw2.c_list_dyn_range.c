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
struct format_opts {int dummy; } ;
struct cmdline_opts {int dummy; } ;
struct buf_pr {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 size_t foreach_state (struct cmdline_opts*,struct format_opts*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,struct buf_pr*) ; 
 int /*<<< orphan*/  list_dyn_state ; 

__attribute__((used)) static int
list_dyn_range(struct cmdline_opts *co, struct format_opts *fo,
    struct buf_pr *bp, caddr_t base, size_t sz)
{

	sz = foreach_state(co, fo, base, sz, list_dyn_state, bp);
	return (sz);
}