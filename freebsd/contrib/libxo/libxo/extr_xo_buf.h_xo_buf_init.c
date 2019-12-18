#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xb_bufp; int /*<<< orphan*/  xb_curp; int /*<<< orphan*/  xb_size; } ;
typedef  TYPE_1__ xo_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  XO_BUFSIZ ; 
 int /*<<< orphan*/  xo_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xo_buf_init (xo_buffer_t *xbp)
{
    xbp->xb_size = XO_BUFSIZ;
    xbp->xb_bufp = xo_realloc(NULL, xbp->xb_size);
    xbp->xb_curp = xbp->xb_bufp;
}