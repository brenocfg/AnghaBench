#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  config; int /*<<< orphan*/  spell_checker; } ;

/* Variables and functions */
 TYPE_1__** SS ; 
 int /*<<< orphan*/  delete_aspell_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_aspell_speller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_email ; 
 int /*<<< orphan*/  re_url ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int spellers ; 

void spell_done (void) {
  int i;
  for (i = 0; i < spellers; i++) {
    delete_aspell_speller (SS[i]->spell_checker);
    delete_aspell_config (SS[i]->config);
  }
  regfree (&re_email);
  regfree (&re_url);
}