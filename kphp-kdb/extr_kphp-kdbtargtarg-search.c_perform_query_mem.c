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
typedef  int /*<<< orphan*/  condition_t ;

/* Variables and functions */
 int /*<<< orphan*/  Qq ; 
 int R_tot ; 
 scalar_t__* User ; 
 int /*<<< orphan*/  build_condition_from_query (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int max_uid ; 
 int /*<<< orphan*/  postprocess_res () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  store_res (int) ; 
 scalar_t__ user_matches_condition (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int verbosity ; 

int perform_query_mem (void) {
  int i;

  if (verbosity > 1) {
    fprintf (stderr, "performing query by complete scanning with pre-compiled condition\n");
  }
  condition_t C = build_condition_from_query (Qq, 1);

  for (i = 0; i <= max_uid; i++) {
    if (User[i] && user_matches_condition (User[i], C, i)) {
      store_res (i);
    }
  }

  postprocess_res();

  return R_tot;
}