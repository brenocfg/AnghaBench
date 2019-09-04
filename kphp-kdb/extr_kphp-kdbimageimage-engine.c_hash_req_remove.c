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
struct forth_request {long long prog_id; struct forth_request* hnext; } ;

/* Variables and functions */
 struct forth_request** H ; 
 int REQ_HASH_SIZE ; 
 int /*<<< orphan*/  requests_in_hash ; 

__attribute__((used)) static int hash_req_remove (struct forth_request *R) {
  long long prog_id = R->prog_id;
  unsigned h = ((unsigned) prog_id) & (REQ_HASH_SIZE - 1);
  struct forth_request **p = H + h, *V;
  while (*p) {
    V = *p;
    if (V == R) {
      *p = V->hnext;
      requests_in_hash--;
      return 1;
    }
    p = &V->hnext;
  }
  return 0;
}