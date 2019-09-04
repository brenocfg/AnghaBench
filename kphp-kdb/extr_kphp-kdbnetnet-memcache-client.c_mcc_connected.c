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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  last_query_sent_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_query ) (struct connection*) ;int /*<<< orphan*/  (* connected ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_1__* MCC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (struct connection*)) ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int /*<<< orphan*/  stub2 (struct connection*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int mcc_connected (struct connection *c) {
  c->last_query_sent_time = precise_now;

  #ifdef AES
  if (verbosity > 1) {
    fprintf (stderr, "connection #%d: connected, crypto_flags = %d\n", c->fd, MCC_DATA(c)->crypto_flags);
  }
  if (MCC_FUNC(c)->mc_check_perm) {
    int res = MCC_FUNC(c)->mc_check_perm (c);
    if (res < 0) {
      return res;
    }
    if (!(res &= 3)) {
      return -1;
    }
    MCC_DATA(c)->crypto_flags = res;
  } else {
    MCC_DATA(c)->crypto_flags = 3;
  }

  if ((MCC_DATA(c)->crypto_flags & 2) && MCC_FUNC(c)->mc_init_crypto) {
    int res = MCC_FUNC(c)->mc_init_crypto (c);

    if (res > 0) {
      assert (MCC_DATA(c)->crypto_flags & 4);
    } else if (!(MCC_DATA(c)->crypto_flags & 1)) {
      return -1;
    }
  }
  #endif

  write_out (&c->Out, "version\r\n", 9);

  //arseny30: added for php-engine:
  if (MCC_FUNC(c)->connected) {
    MCC_FUNC(c)->connected (c);
  }

  assert (MCC_FUNC(c)->flush_query);
  MCC_FUNC(c)->flush_query (c);

  return 0;
}