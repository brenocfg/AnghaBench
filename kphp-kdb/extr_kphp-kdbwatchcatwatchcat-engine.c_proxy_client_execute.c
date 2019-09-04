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
struct mcc_data {int key_len; int arg_num; int response_len; } ;
struct connection {int /*<<< orphan*/  last_response_time; } ;

/* Variables and functions */
 struct mcc_data* MCC_DATA (struct connection*) ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int proxy_client_execute (struct connection *c, int op) {
  struct mcc_data *D = MCC_DATA(c);

  if (verbosity > 0) {
    fprintf (stderr, "proxy_mc_client: op=%d, key_len=%d, arg#=%d, response_len=%d\n", op, D->key_len, D->arg_num, D->response_len);
  }

  c->last_response_time = precise_now;
  return SKIP_ALL_BYTES;
}