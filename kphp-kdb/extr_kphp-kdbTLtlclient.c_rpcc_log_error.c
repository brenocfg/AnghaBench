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
 int* P ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  log_printf (char*,int,int,char*) ; 
 int tl_fetch_string (int*,int,char**,int*,int /*<<< orphan*/ ) ; 

int rpcc_log_error (int len) {
  assert (!(len % 4));
  int code = P[5], ilen = (len / 4) - 7;
  int l;
  char *text;
  assert (ilen > 0);
  int r = tl_fetch_string (&P[6], ilen, &text, &l, 0);
  assert (r == ilen);
  log_printf ("Receive RPC_REQ_ERROR (code: %d, text: \"%.*s\")\n", code, l, text);
  return 0;
}