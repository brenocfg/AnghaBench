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
struct TYPE_5__ {int nmode; TYPE_2__ const* modes; } ;
typedef  TYPE_1__ XRRScreenResources ;
struct TYPE_6__ {scalar_t__ id; } ;
typedef  TYPE_2__ XRRModeInfo ;
typedef  scalar_t__ RRMode ;

/* Variables and functions */

__attribute__((used)) static const XRRModeInfo* getModeInfo(const XRRScreenResources* sr, RRMode id)
{
    int i;

    for (i = 0;  i < sr->nmode;  i++)
    {
        if (sr->modes[i].id == id)
            return sr->modes + i;
    }

    return NULL;
}