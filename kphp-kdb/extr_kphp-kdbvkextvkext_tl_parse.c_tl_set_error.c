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
struct TYPE_2__ {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ strdup (char const*) ; 
 TYPE_1__ tl ; 

void tl_set_error (const char *error) {
  if (tl.error) { return; }
  tl.error = strdup (error);
}