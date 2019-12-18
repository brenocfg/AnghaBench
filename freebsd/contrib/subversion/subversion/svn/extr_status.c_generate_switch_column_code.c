#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ file_external; scalar_t__ switched; } ;
typedef  TYPE_1__ svn_client_status_t ;

/* Variables and functions */

__attribute__((used)) static char
generate_switch_column_code(const svn_client_status_t *status)
{
  if (status->switched)
    return 'S';
  else if (status->file_external)
    return 'X';
  else
    return ' ';
}