#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ total_alloc; } ;
typedef  TYPE_1__ GDash ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xmalloc (int) ; 

GDash *
new_gdash (void)
{
  GDash *dash = xmalloc (sizeof (GDash));
  memset (dash, 0, sizeof *dash);
  dash->total_alloc = 0;

  return dash;
}