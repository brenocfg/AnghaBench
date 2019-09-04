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
 int /*<<< orphan*/  TL_ERROR_BAD_VALUE ; 
 int log_split_min ; 
 int log_split_mod ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int check_vector_id (int vector_id) {
  if (vector_id <= 0) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "vector_id isn't positive");
    return -1;
  }
  if (vector_id % log_split_mod != log_split_min) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "wrong split: vector_id = %d, log_split_min = %d, log_split_mod = %d", vector_id, log_split_min, log_split_mod);
    return -1;
  }
  return 0;
}