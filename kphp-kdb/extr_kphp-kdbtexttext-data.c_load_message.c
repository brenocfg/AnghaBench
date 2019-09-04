#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct file_user_list_entry* dir_entry; } ;
typedef  TYPE_1__ user_t ;
struct imessage {int dummy; } ;
struct file_user_list_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ conv_uid (int) ; 
 TYPE_1__* get_user (int) ; 
 int load_message_internal (struct imessage*,TYPE_1__*,struct file_user_list_entry*,int,int,int) ; 
 struct file_user_list_entry* lookup_user_directory (int) ; 

int load_message (struct imessage *M, int user_id, int local_id, int force) {
  user_t *U;
  struct file_user_list_entry *D;

  if (conv_uid (user_id) < 0 || local_id <= 0) {
    return -1;
  }
  
  U = get_user (user_id);
  if (U) {
    D = U->dir_entry;
  } else {
    D = lookup_user_directory (user_id);
  }

  return load_message_internal (M, U, D, user_id, local_id, force);
}