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
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ t10_dif_separate_capable; } ;
struct TYPE_6__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;

/* Variables and functions */
 scalar_t__ sli_get_dif_capable (TYPE_2__*) ; 

__attribute__((used)) static inline uint32_t
sli_is_dif_separate_capable(sli4_t *sli4)
{
	return sli_get_dif_capable(sli4) && sli4->config.t10_dif_separate_capable;
}