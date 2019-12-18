#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gmap {int dummy; } ;
struct TYPE_2__ {scalar_t__ gmap; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 

struct gmap *gmap_get_enabled(void)
{
	return (struct gmap *) S390_lowcore.gmap;
}