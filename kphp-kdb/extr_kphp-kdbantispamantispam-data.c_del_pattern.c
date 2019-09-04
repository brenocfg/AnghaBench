#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ lev_antispam_del_pattern_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ antispam_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_printf (char*,int /*<<< orphan*/ ) ; 
 int verbosity ; 

__attribute__((used)) static bool del_pattern (lev_antispam_del_pattern_t* E) {
  if (antispam_del (E->id)) {
    if (verbosity >= 3) {
      st_printf ("$1del pattern[%10d]$^\n", E->id);
    }
    return TRUE;
  }
  if (verbosity >= 3) {
    st_printf ("$5del pattern[%10d] (rejected: possibly wrong id)$^\n", E->id);
  }
  return FALSE;
}