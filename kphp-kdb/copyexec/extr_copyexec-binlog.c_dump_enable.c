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
struct lev_copyexec_result_enable {scalar_t__ type; int /*<<< orphan*/  random_tag; } ;

/* Variables and functions */
 scalar_t__ LEV_COPYEXEC_RESULT_ENABLE ; 
 scalar_t__ dump_line_header (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static void dump_enable (struct lev_copyexec_result_enable *E) {
  if (dump_line_header (E->type == LEV_COPYEXEC_RESULT_ENABLE ? "LEV_COPYEXEC_RESULT_ENABLE": "LEV_COPYEXEC_RESULT_DISABLE") ) {
    return;
  }
  fprintf (out, "0x%llx\n", E->random_tag);
}