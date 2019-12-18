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
struct run {int notes_num_allocated; char** notes_data; } ;

/* Variables and functions */
 scalar_t__ realloc (char**,int) ; 

__attribute__((used)) static int
run_notes_expand_to_hold_more(struct run *msg)
{
  int tobe_allocated = msg->notes_num_allocated;
  char ** new_data = NULL;
  tobe_allocated = !tobe_allocated ? 1 : tobe_allocated << 1;
  new_data = (char **) realloc(msg->notes_data,
      tobe_allocated * sizeof(char *));
  if (new_data == NULL)
    return -1;
  msg->notes_data = new_data;
  msg->notes_num_allocated = tobe_allocated;
  return 0;}