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
struct type {int dummy; } ;

/* Variables and functions */
 struct type** undef_types ; 
 int undef_types_allocated ; 
 scalar_t__ undef_types_length ; 
 scalar_t__ xmalloc (int) ; 

void
_initialize_stabsread (void)
{
  undef_types_allocated = 20;
  undef_types_length = 0;
  undef_types = (struct type **)
    xmalloc (undef_types_allocated * sizeof (struct type *));
}