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

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ INI_STR (char*) ; 
 scalar_t__ PING_TIMEOUT ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atof (scalar_t__) ; 
 scalar_t__ buffer_delete (scalar_t__) ; 
 scalar_t__ inbuf ; 
 long long last_qid ; 
 int last_queue_id ; 
 int lrand48 () ; 
 int /*<<< orphan*/  minit ; 
 scalar_t__ ping_timeout ; 
 scalar_t__ read_tl_config (scalar_t__) ; 

void rpc_on_minit (int module_number) { /* {{{ */
  ADD_CNT (minit);
  START_TIMER (minit);
  last_qid = lrand48 () * (1ll << 32) + lrand48 () + 1000000;;
  last_queue_id = (1 << 30) * 1ll + lrand48 (); 
  if (INI_STR ("tl.conffile")) {
    assert (read_tl_config (INI_STR ("tl.conffile")) >= 0);
    if (inbuf) {
      inbuf = buffer_delete (inbuf);
    }
  }
  if (INI_STR ("vkext.ping_timeout")) {
    ping_timeout = atof (INI_STR ("vkext.ping_timeout"));
    if (ping_timeout <= 0) {
      ping_timeout = PING_TIMEOUT;
    }
  }
  END_TIMER (minit);
}