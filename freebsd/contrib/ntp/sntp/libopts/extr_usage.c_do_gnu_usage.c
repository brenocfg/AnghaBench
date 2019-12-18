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
struct TYPE_3__ {int fOptSet; } ;
typedef  TYPE_1__ tOptions ;

/* Variables and functions */
 int OPTPROC_GNUUSAGE ; 

__attribute__((used)) static inline bool
do_gnu_usage(tOptions * pOpts)
{
    return (pOpts->fOptSet & OPTPROC_GNUUSAGE) ? true : false;
}