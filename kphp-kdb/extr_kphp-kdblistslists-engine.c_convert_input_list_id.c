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
typedef  int /*<<< orphan*/  input_list_id_t ;

/* Variables and functions */

__attribute__((used)) static inline int convert_input_list_id (const char *s, input_list_id_t list_id) {
#ifdef LISTS_Z
  return convert_ints_array (s, list_id, list_id_ints);
#else
  return 1;
#endif
}