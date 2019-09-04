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
struct raw_message {scalar_t__ magic; int total_bytes; } ;

/* Variables and functions */
 scalar_t__ RM_INIT_MAGIC ; 
 scalar_t__ RM_TMP_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hexdump (char*,char*) ; 
 int /*<<< orphan*/  rwm_clone (struct raw_message*,struct raw_message*) ; 
 int rwm_fetch_data (struct raw_message*,char*,int) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 
 int /*<<< orphan*/  stderr ; 

int rwm_dump (struct raw_message *raw) {
  assert (raw->magic == RM_INIT_MAGIC || raw->magic == RM_TMP_MAGIC);
  struct raw_message t;
  rwm_clone (&t, raw);
  static char R[10004];
  int r = rwm_fetch_data (&t, R, 10004);
  int x = (r > 10000) ? 10000 : r;
  hexdump (R, R + x);
  if (r > x) {
    fprintf (stderr, "%d bytes not printed\n", raw->total_bytes - x);
  }
  rwm_free (&t);
  return 0;
}