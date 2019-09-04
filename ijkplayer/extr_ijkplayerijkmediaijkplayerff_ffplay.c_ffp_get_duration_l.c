#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {TYPE_1__* ic; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_8__ {TYPE_2__* is; } ;
struct TYPE_6__ {int /*<<< orphan*/  duration; } ;
typedef  TYPE_3__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 scalar_t__ fftime_to_milliseconds (int /*<<< orphan*/ ) ; 

long ffp_get_duration_l(FFPlayer *ffp)
{
    assert(ffp);
    VideoState *is = ffp->is;
    if (!is || !is->ic)
        return 0;

    int64_t duration = fftime_to_milliseconds(is->ic->duration);
    if (duration < 0)
        return 0;

    return (long)duration;
}