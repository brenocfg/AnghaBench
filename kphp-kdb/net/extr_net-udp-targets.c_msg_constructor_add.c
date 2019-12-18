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
struct udp_target {int /*<<< orphan*/  constructors; int /*<<< orphan*/  max_confirmed; int /*<<< orphan*/  send_num; } ;
struct udp_msg_constructor {int msg_num; int total_parts; int parts; struct raw_message* msgs; } ;
struct udp_msg {int dummy; } ;
struct raw_message {int magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_force_confirm (struct udp_target*,int) ; 
 int /*<<< orphan*/  add_received (struct udp_target*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct udp_msg_constructor*) ; 
 int /*<<< orphan*/  lrand48 () ; 
 struct udp_msg_constructor* malloc (int) ; 
 int /*<<< orphan*/  memset (struct raw_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msg_is_dup (struct udp_target*,int) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 
 int /*<<< orphan*/  rwm_union (struct raw_message*,struct raw_message*) ; 
 int /*<<< orphan*/  tree_delete_udp_msg_constructor (int /*<<< orphan*/ ,struct udp_msg_constructor*) ; 
 int /*<<< orphan*/  tree_insert_udp_msg_constructor (int /*<<< orphan*/ ,struct udp_msg_constructor*,int /*<<< orphan*/ ) ; 
 struct udp_msg_constructor** tree_lookup_value_udp_msg_constructor (int /*<<< orphan*/ ,void*) ; 
 struct udp_msg* udp_msg_create (struct raw_message*,int,struct udp_target*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,...) ; 

struct udp_msg *msg_constructor_add (struct raw_message *raw, int packet_id, int part, int total_parts, struct udp_target *S) {
  assert (packet_id >= 0);
  add_force_confirm (S, packet_id + part);
  if (msg_is_dup (S, packet_id + part)) {
    vkprintf (1, "msg_is_dup: duplicate message %d. S->send_num = %d, S->max_confirmed = %d\n", packet_id, S->send_num, S->max_confirmed);
    rwm_free (raw);
    return 0;
  }
  add_received (S, packet_id + part);
  struct udp_msg_constructor **_M = tree_lookup_value_udp_msg_constructor (S->constructors, (void *)&packet_id);
  struct udp_msg_constructor *M;
  if (_M) {
    M = *_M;
  } else {
    M = malloc (sizeof (*M) + total_parts * sizeof (struct raw_message));
    M->msg_num = packet_id;
    M->total_parts = total_parts;
    M->parts = total_parts;
    memset (M->msgs, 0, total_parts * sizeof (struct raw_message));
    S->constructors = tree_insert_udp_msg_constructor (S->constructors, M, lrand48 ());
  }
//  rwm_clone (&M->msgs[part], raw);
  M->msgs[part] = *raw;
  M->parts --;
  vkprintf (3, "packet_id = %d. %d parts left\n", packet_id, M->parts);
  if (M->parts) { return 0; }
  struct raw_message *r = &M->msgs[0];
  int i;
  for (i = 1; i < M->total_parts; i++) {
    assert (M->msgs[i].magic);
    rwm_union (r, &M->msgs[i]);
  }

  struct udp_msg *msg = udp_msg_create (r, packet_id, S);

  S->constructors = tree_delete_udp_msg_constructor (S->constructors, M);
  free (M);
  
  return msg;
}