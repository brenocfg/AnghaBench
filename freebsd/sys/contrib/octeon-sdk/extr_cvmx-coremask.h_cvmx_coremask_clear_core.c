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
struct cvmx_coremask {unsigned long long* coremask_bitmap; } ;

/* Variables and functions */
 int CVMX_COREMASK_HLDRSZ ; 

__attribute__((used)) static inline int cvmx_coremask_clear_core(struct cvmx_coremask *pcm,
    int core)
{
    int n, i;

    n = core % CVMX_COREMASK_HLDRSZ;
    i = core / CVMX_COREMASK_HLDRSZ;
    pcm->coremask_bitmap[i] &= ~(1ull << n);

    return 0;
}