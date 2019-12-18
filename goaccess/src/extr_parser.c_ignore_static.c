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
struct TYPE_2__ {scalar_t__ ignore_statics; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 scalar_t__ is_static (char const*) ; 

__attribute__((used)) static int
ignore_static (const char *req)
{
  if (conf.ignore_statics && is_static (req))
    return 1;
  return 0;
}