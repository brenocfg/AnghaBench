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
struct TYPE_2__ {scalar_t__ ignore_status_idx; int /*<<< orphan*/  ignore_status; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int str_inarray (char const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ignore_status_code (const char *status)
{
  if (conf.ignore_status_idx == 0)
    return 0;

  if (str_inarray (status, conf.ignore_status, conf.ignore_status_idx) != -1)
    return 1;
  return 0;
}