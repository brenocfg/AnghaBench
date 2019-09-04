#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* msgs; } ;
typedef  TYPE_1__ user_mod_header_t ;
struct TYPE_6__ {int user_id; int message_id; int hc; int /*<<< orphan*/ * hashes; struct TYPE_6__* prev; } ;
typedef  TYPE_2__ message_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 TYPE_2__* dyn_alloc (int,int) ; 
 TYPE_1__* dyn_user_header (int,int) ; 
 int /*<<< orphan*/  tot_kept_messages ; 
 int tot_kept_msg_bytes ; 

hash_t *dyn_alloc_new_msg (int user_id, int message_id, int hcount) {
  user_mod_header_t *H = dyn_user_header(user_id, 1);
  message_t *R;
  int size = sizeof(message_t) + (hcount - 1)*sizeof(hash_t);
  if (!H) { return 0; }
  R = dyn_alloc (size, sizeof(int));
  if (!R) { return 0; }
  R->prev = H->msgs;
  R->user_id = user_id;
  R->message_id = message_id;
  R->hc = hcount;
  H->msgs = R;
  tot_kept_messages++;
  tot_kept_msg_bytes += size;
  return R->hashes;
}