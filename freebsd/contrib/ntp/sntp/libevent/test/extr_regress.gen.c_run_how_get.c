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
struct run {int how_set; char* how_data; } ;

/* Variables and functions */

int
run_how_get(struct run *msg, char * *value)
{
  if (msg->how_set != 1)
    return (-1);
  *value = msg->how_data;
  return (0);
}