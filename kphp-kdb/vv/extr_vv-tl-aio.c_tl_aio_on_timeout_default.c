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
struct tl_saved_query {int failed; int /*<<< orphan*/  (* free_extra ) (struct tl_saved_query*) ;int /*<<< orphan*/  wait_num; int /*<<< orphan*/  error_code; } ;
struct conn_query {struct tl_saved_query* extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_AIO_TIMEOUT ; 
 int /*<<< orphan*/  expired_aio_queries ; 
 int /*<<< orphan*/  stub1 (struct tl_saved_query*) ; 
 int /*<<< orphan*/  tl_aio_fail_start (struct tl_saved_query*) ; 
 int /*<<< orphan*/  tl_delete_aio_query (struct conn_query*) ; 
 int /*<<< orphan*/  zfree (struct tl_saved_query*,int) ; 

int tl_aio_on_timeout_default (struct conn_query *Q) {
  struct tl_saved_query *q = Q->extra;
  q->wait_num --;
  expired_aio_queries ++;
  if (!q->failed) {
    q->error_code = TL_ERROR_AIO_TIMEOUT;
    //q->fail (q);
    tl_aio_fail_start (q);
  }
  q->failed = 1;
  if (!q->wait_num) {
    q->free_extra (q);
    zfree (q, sizeof (*q));
  }
  tl_delete_aio_query (Q);
  return 0;
}