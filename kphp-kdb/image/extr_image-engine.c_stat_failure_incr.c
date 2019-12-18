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
struct stat_failure {scalar_t__ size; int /*<<< orphan*/ * prog; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  total; } ;
struct forth_request {scalar_t__ size; int /*<<< orphan*/ * prog; int /*<<< orphan*/  prog_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stat_failure_incr (struct stat_failure *S, struct forth_request *E) {
  S->total++;
  S->prog_id = E->prog_id;
  if (S->prog) {
    free (S->prog);
  }
  S->prog = E->prog;
  S->size = E->size;
  E->prog = NULL;
  E->size = 0;
}