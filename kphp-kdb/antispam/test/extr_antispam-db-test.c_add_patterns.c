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
struct TYPE_3__ {int /*<<< orphan*/  uahash; int /*<<< orphan*/  flags; int /*<<< orphan*/  ip; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ antispam_pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int N ; 
 int /*<<< orphan*/ * _flag ; 
 int /*<<< orphan*/ * _id ; 
 int /*<<< orphan*/ * _ip ; 
 int /*<<< orphan*/ * _uahash ; 
 int /*<<< orphan*/  antispam_add (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double current_time () ; 
 int /*<<< orphan*/  dyn_free_bytes () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,...) ; 
 int /*<<< orphan*/  memory_statistic () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * str ; 

__attribute__((used)) static void add_patterns (void) {
  int i;
  fprintf (stderr, "[%6.2f] Add all patterns... [free bytes = %ld] ", current_time(), dyn_free_bytes());
  for (i = 0; i < N; i++) {
    antispam_pattern_t p;
    p.id = _id[i];
    p.ip = _ip[i];
    p.flags = _flag[i];
    p.uahash = _uahash[i];
    antispam_add (p, str[i], FALSE);
  }
  fprintf (stderr, "OK [free bytes = %ld]\n", dyn_free_bytes());
  memory_statistic();
}