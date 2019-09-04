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
typedef  int /*<<< orphan*/  pattern_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  antispam_del_unsafe (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  id_to_pattern ; 
 int /*<<< orphan*/ * id_to_pattern_find (int /*<<< orphan*/ ,int) ; 

bool antispam_del (int id) {
  pattern_t *pattern = id_to_pattern_find (id_to_pattern, id);
  if (pattern == 0) {
    return FALSE;
  }
  antispam_del_unsafe (id, pattern);
  return TRUE;
}