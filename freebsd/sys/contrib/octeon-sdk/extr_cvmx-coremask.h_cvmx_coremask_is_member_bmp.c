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
struct cvmx_coremask {int dummy; } ;

/* Variables and functions */
 int cvmx_coremask_is_set_core (struct cvmx_coremask*,int) ; 
 scalar_t__ cvmx_get_core_num () ; 

__attribute__((used)) static inline int cvmx_coremask_is_member_bmp(struct cvmx_coremask *pcm)
{
    return cvmx_coremask_is_set_core(pcm, (int)cvmx_get_core_num());
}