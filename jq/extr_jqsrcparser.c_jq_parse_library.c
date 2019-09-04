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
struct locfile {int dummy; } ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  OP_IS_CALL_PSEUDO ; 
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ block_has_main (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_has_only_binders_and_imports (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jq_parse (struct locfile*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locfile_locate (struct locfile*,int /*<<< orphan*/ ,char*) ; 

int jq_parse_library(struct locfile* locations, block* answer) {
  int errs = jq_parse(locations, answer);
  if (errs) return errs;
  if (block_has_main(*answer)) {
    locfile_locate(locations, UNKNOWN_LOCATION, "jq: error: library should only have function definitions, not a main expression");
    return 1;
  }
  assert(block_has_only_binders_and_imports(*answer, OP_IS_CALL_PSEUDO));
  return 0;
}