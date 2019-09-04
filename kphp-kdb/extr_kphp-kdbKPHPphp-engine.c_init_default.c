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
struct TYPE_2__ {short port; } ;

/* Variables and functions */
 int MAX_CONNECTIONS ; 
 TYPE_1__ PID ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ *) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  dl_set_default_handlers () ; 
 int dynamic_data_buffer_size ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int maxconn ; 
 int now ; 
 int /*<<< orphan*/  pid ; 
 scalar_t__ raise_file_rlimit (int) ; 
 scalar_t__ rpc_port ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 char* username ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

void init_default() {
  dl_set_default_handlers();
  now = (int)time (NULL);

  pid = getpid();
  // RPC part
  PID.port = (short)rpc_port;

  dynamic_data_buffer_size = (1 << 26);//26 for struct conn_query
  init_dyn_data();

  if (!username && maxconn == MAX_CONNECTIONS && geteuid()) {
    maxconn = 1000; //not for root
  }

  if (raise_file_rlimit (maxconn + 16) < 0) {
    vkprintf (-1, "fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  aes_load_pwd_file (NULL);

  if (change_user (username) < 0) {
    vkprintf (-1, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }
}