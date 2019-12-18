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
struct io_state {int /*<<< orphan*/  uio; int /*<<< orphan*/  fp; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int __sprint (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
io_flush(struct io_state *iop, locale_t locale)
{

	return (__sprint(iop->fp, &iop->uio, locale));
}