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
struct repl_server_status {char* wptr; char* rptr; } ;

/* Variables and functions */
 int LEV_ROTATE_TO ; 
 int load_byte (struct repl_server_status*,char**) ; 

int check_last36_bytes (struct repl_server_status *S) {
  char *ptr = S->wptr;
  int val = 0, res = 0, i;
  for (i = 0; i < 36 && ptr != S->rptr; i++) {
    val = (val << 8) | load_byte (S, &ptr);
    if (val == LEV_ROTATE_TO) {
      res = i + 1;
    }
  }
  return res;
}