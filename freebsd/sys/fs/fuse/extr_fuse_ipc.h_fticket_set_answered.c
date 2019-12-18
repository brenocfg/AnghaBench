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
struct fuse_ticket {int /*<<< orphan*/  tk_flag; int /*<<< orphan*/  tk_aw_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ANSW ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fticket_set_answered(struct fuse_ticket *ftick)
{
	mtx_assert(&ftick->tk_aw_mtx, MA_OWNED);
	ftick->tk_flag |= FT_ANSW;
}