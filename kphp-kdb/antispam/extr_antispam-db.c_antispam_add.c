#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pattern_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ antispam_pattern_t ;

/* Variables and functions */
 int FALSE ; 
 int add_unsafe (TYPE_1__,char const*) ; 
 int /*<<< orphan*/  antispam_del_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  id_to_pattern ; 
 int /*<<< orphan*/ * id_to_pattern_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool antispam_add (antispam_pattern_t p, const char *s, bool replace) {
  pattern_t *pattern = id_to_pattern_find (id_to_pattern, p.id);
  if (pattern != 0) {
    if (!replace) {
      return FALSE;
    }
    antispam_del_unsafe (p.id, pattern);
  }
  return add_unsafe (p, s);
}