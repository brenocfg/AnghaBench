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
struct _qs {int dummy; } ;
struct _cfg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
null_run_fn(struct _qs *q, struct _cfg *cfg)
{
    (void)q;
    (void)cfg;
    return 0;
}