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
struct connection {int /*<<< orphan*/  In; int /*<<< orphan*/  last_response_time; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  qres_t ;
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
#define  RPC_PONG 130 
#define  RPC_REQ_ERROR 129 
#define  RPC_REQ_RESULT 128 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * get_qres (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  got_result (long long) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  nbit_clear (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  qr_ans ; 
 int /*<<< orphan*/  qres_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qres_save (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int,int) ; 

int rpcc_execute (struct connection *c, int op, int len) {
  vkprintf (1, "rpcc_execute: fd=%d, op=%d, len=%d\n", c->fd, op, len);

  int head[5];
  qres_t *qres;

  nb_iterator_t Iter;

  char *data;
  int data_len;

  c->last_response_time = precise_now;

  switch (op) {
    case RPC_REQ_ERROR:
    case RPC_REQ_RESULT:
      assert (len % (int)sizeof (int) == 0);
      len /= (int)sizeof (int);
      assert (len >= 6);

      nbit_set (&Iter, &c->In);
      assert (nbit_read_in (&Iter, head, sizeof (int) * 5) == sizeof (int) * 5);

      long long id = *(long long *)(&head[3]);

      qres = get_qres (id, qr_ans);
      if (qres == NULL) {
        got_result (id);
        break;
      }

      if (op == RPC_REQ_ERROR) {
        qres_error (qres);
        break;
      }

      data_len = len - 5 - 1;
      data = malloc (sizeof (int) * (size_t)data_len);
      assert (nbit_read_in (&Iter, data, data_len * (int)sizeof (int)) == data_len * (int)sizeof (int));

      nbit_clear (&Iter);

      if (qres_save (qres, data, data_len * (int)sizeof (int)) < 0) {
        free (data);
      }

      break;
    case RPC_PONG:
      break;
  }

  return SKIP_ALL_BYTES;
}