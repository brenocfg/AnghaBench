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
 int /*<<< orphan*/  fid_id ; 
 int /*<<< orphan*/  fid_name_id ; 
 int /*<<< orphan*/  fids ; 
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_string_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scores ; 
 int /*<<< orphan*/  users ; 
 int /*<<< orphan*/  vector_free (int /*<<< orphan*/ ) ; 

void data_free (void) {
  map_string_int_free (&fid_name_id);

  map_int_int_free (&fid_id);
  vector_free (fids);

  vector_free (scores);
  vector_free (users);
}