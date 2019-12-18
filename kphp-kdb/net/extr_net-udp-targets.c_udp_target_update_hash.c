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
struct udp_target {int generation; int /*<<< orphan*/  hash; int /*<<< orphan*/  PID; } ;

/* Variables and functions */
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  crc64 (int*,int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tree_delete_udp_target_by_hash (int /*<<< orphan*/ ,struct udp_target*) ; 
 int /*<<< orphan*/  tree_insert_udp_target_by_hash (int /*<<< orphan*/ ,struct udp_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_target_by_hash ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

void udp_target_update_hash (struct udp_target *S) {
  static int P[7];
  int x = memcmp (&PID, &S->PID, 12);
  if (x < 0) {
    memcpy (P, &PID, 12);
    memcpy (P + 3, &S->PID, 12);
  } else {
    memcpy (P, &S->PID, 12);
    memcpy (P + 3, &PID, 12);
  }
  P[6] = S->generation;
  if (S->hash) {
    vkprintf (2, "delete: hash = %lld\n", S->hash);
    udp_target_by_hash  = tree_delete_udp_target_by_hash (udp_target_by_hash, S);
  }
  S->hash = crc64 (P, 28);
  vkprintf (2, "insert: hash = %lld\n", S->hash);
  udp_target_by_hash = tree_insert_udp_target_by_hash (udp_target_by_hash, S, lrand48 ());
}