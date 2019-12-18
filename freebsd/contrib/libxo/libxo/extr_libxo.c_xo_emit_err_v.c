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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  xo_emit_warn_hcv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_finish () ; 

void
xo_emit_err_v (int eval, int code, const char *fmt, va_list vap)
{
    xo_emit_warn_hcv(NULL, 0, code, fmt, vap);
    xo_finish();
    exit(eval);
}