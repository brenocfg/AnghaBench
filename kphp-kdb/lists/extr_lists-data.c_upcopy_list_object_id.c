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
struct lev_new_entry {int /*<<< orphan*/  object_id; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */

__attribute__((used)) static inline void upcopy_list_object_id (void *E, list_id_t list_id, object_id_t object_id) {
  ((struct lev_new_entry *)E)->object_id = object_id;
}