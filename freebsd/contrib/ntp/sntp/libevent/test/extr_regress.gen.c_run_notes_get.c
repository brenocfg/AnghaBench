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
struct run {int notes_length; char** notes_data; int /*<<< orphan*/  notes_set; } ;

/* Variables and functions */

int
run_notes_get(struct run *msg, int offset,
    char * *value)
{
  if (!msg->notes_set || offset < 0 || offset >= msg->notes_length)
    return (-1);
  *value = msg->notes_data[offset];
  return (0);
}