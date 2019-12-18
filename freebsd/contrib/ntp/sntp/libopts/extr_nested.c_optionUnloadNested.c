#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nestVal; } ;
struct TYPE_6__ {scalar_t__ valType; TYPE_1__ v; } ;
typedef  TYPE_2__ tOptionValue ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ OPARG_TYPE_HIERARCHY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  unload_arg_list (int /*<<< orphan*/ ) ; 

void
optionUnloadNested(tOptionValue const * opt_val)
{
    if (opt_val == NULL) return;
    if (opt_val->valType != OPARG_TYPE_HIERARCHY) {
        errno = EINVAL;
        return;
    }

    unload_arg_list(opt_val->v.nestVal);

    AGFREE(opt_val);
}