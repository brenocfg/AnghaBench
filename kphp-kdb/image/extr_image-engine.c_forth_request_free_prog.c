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
struct forth_request {scalar_t__ size; int /*<<< orphan*/ * prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_results_memory ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  results_unload_bytes ; 
 int /*<<< orphan*/  unloaded_results ; 

__attribute__((used)) static void forth_request_free_prog (struct forth_request *E) {
  if (E->prog != NULL) {
    unloaded_results++;
    results_unload_bytes += E->size + 1;
    all_results_memory -= E->size + 1;
    free (E->prog);
    E->prog = NULL;
    E->size = 0;
  }
}