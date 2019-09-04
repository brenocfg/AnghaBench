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
struct copyexec_rpc_handshake {scalar_t__ hostname_length; int /*<<< orphan*/  hostname; int /*<<< orphan*/  pid; scalar_t__ random_tag; scalar_t__ volume_id; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPYEXEC_RPC_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  Q ; 
 int /*<<< orphan*/  client_state_to_str (scalar_t__) ; 
 scalar_t__ cur_client_state ; 
 int /*<<< orphan*/  detect_hostname () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  handshake_sent_time ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ main_volume_id ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  now ; 
 scalar_t__ random_tag ; 
 struct copyexec_rpc_handshake* rpc_create_query (int /*<<< orphan*/ ,scalar_t__,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (int /*<<< orphan*/ ,struct connection*) ; 
 scalar_t__ st_handshake_sent ; 
 scalar_t__ st_startup ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int rpc_send_handshake (struct connection *c) {
  vkprintf (3, "rpc_send_handshake (c: %p)\n", c);
  if (cur_client_state != st_startup) {
    vkprintf (2, "rpc_send_handshake: reconnection. cur_client_state %s\n", client_state_to_str (cur_client_state));
  }
  if (!main_volume_id) {
    kprintf ("rpc_send_handshake: main_volume_id isn't initialized.\n");
    exit (1);
  }
  if (!random_tag) {
    kprintf ("rpc_send_handshake: random_tag isn't initialized.\n");
    exit (1);
  }
  detect_hostname ();
  struct copyexec_rpc_handshake *E = rpc_create_query (Q, sizeof (*E) + strlen (hostname), c, COPYEXEC_RPC_TYPE_HANDSHAKE);
  if (E == NULL) {
    vkprintf (2, "rpc_send_handshake: rpc_create_query returns NULL.\n");
    return -__LINE__;
  }
  E->volume_id = main_volume_id;
  E->random_tag = random_tag;
  E->hostname_length = strlen (hostname);
  E->pid = getpid ();
  memcpy (E->hostname, hostname, E->hostname_length);
  cur_client_state = st_handshake_sent;
  handshake_sent_time = now;
  return rpc_send_query (Q, c);
}