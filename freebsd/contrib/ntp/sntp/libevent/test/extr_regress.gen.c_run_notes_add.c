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
struct run {scalar_t__ notes_length; scalar_t__ notes_num_allocated; char** notes_data; int notes_set; } ;

/* Variables and functions */
 scalar_t__ run_notes_expand_to_hold_more (struct run*) ; 
 char* strdup (char const*) ; 

char * *
run_notes_add(struct run *msg, const char * value)
{
  if (++msg->notes_length >= msg->notes_num_allocated) {
    if (run_notes_expand_to_hold_more(msg)<0)
      goto error;
  }
  if (value != NULL) {
    msg->notes_data[msg->notes_length - 1] = strdup(value);
    if (msg->notes_data[msg->notes_length - 1] == NULL) {
      goto error;
    }
  } else {
    msg->notes_data[msg->notes_length - 1] = NULL;
  }
  msg->notes_set = 1;
  return &(msg->notes_data[msg->notes_length - 1]);
error:
  --msg->notes_length;
  return (NULL);
}