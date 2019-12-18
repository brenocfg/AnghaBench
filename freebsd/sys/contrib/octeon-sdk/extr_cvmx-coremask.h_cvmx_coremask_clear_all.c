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
struct cvmx_coremask {scalar_t__* coremask_bitmap; } ;

/* Variables and functions */
 int CVMX_COREMASK_BMPSZ ; 

__attribute__((used)) static inline int cvmx_coremask_clear_all(struct cvmx_coremask *pcm)
{
    int i;

    for (i = 0; i < CVMX_COREMASK_BMPSZ; i++)
        pcm->coremask_bitmap[i] = 0;

    return 0;
}