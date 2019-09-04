#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int module; } ;
typedef  TYPE_1__ GColors ;

/* Variables and functions */
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static GColors *
new_gcolors (void)
{
  GColors *color = xcalloc (1, sizeof (GColors));
  color->module = -1;

  return color;
}