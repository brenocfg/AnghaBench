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
struct gather_entry {int res_bytes; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ zzmalloc (int) ; 

__attribute__((used)) static int client_result_alloc (struct gather_entry *E, char **to) {
  //int b = E->res_read;
  //assert (b >= 4 && b <= E->res_bytes);
  if (!E->res_bytes) {
    return 0;
  }
  E->data = zzmalloc (E->res_bytes + 4);
  *to = (char *) E->data;
  return E->res_bytes + 4;
}