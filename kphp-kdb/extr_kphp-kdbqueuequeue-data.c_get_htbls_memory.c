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
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  h_qkey ; 
 int /*<<< orphan*/  h_queue ; 
 int /*<<< orphan*/  h_subscribers ; 
 long hset_llp_get_memory_used (int /*<<< orphan*/ *) ; 
 long map_int_int_get_memory_used (int /*<<< orphan*/ *) ; 
 long map_ll_vptr_get_memory_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secrets ; 
 long shmap_string_vptr_get_memory_used (int /*<<< orphan*/ *) ; 

long get_htbls_memory (void) {
  return shmap_string_vptr_get_memory_used (&h_queue) +
         shmap_string_vptr_get_memory_used (&h_qkey) +
         map_int_int_get_memory_used (&secrets) +
         map_ll_vptr_get_memory_used (&alias) +
         hset_llp_get_memory_used (&h_subscribers);
}