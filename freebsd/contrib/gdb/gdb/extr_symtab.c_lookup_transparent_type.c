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
struct type {int dummy; } ;
struct TYPE_2__ {struct type* (* la_lookup_transparent_type ) (char const*) ;} ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 struct type* stub1 (char const*) ; 

struct type *
lookup_transparent_type (const char *name)
{
  return current_language->la_lookup_transparent_type (name);
}