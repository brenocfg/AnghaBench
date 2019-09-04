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
struct forth_request {int /*<<< orphan*/ * prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forth_request_free_prog (struct forth_request*) ; 
 int /*<<< orphan*/  hash_req_remove (struct forth_request*) ; 
 int /*<<< orphan*/  tlist_insert (int /*<<< orphan*/ *,struct forth_request*) ; 
 int /*<<< orphan*/  tlist_remove (int /*<<< orphan*/ *,struct forth_request*) ; 
 int /*<<< orphan*/  with_output_free_list ; 
 int /*<<< orphan*/  without_output_free_list ; 

__attribute__((used)) static void forth_request_unload_prog (struct forth_request *E) {
  tlist_remove (&with_output_free_list, E);
  assert (E->prog != NULL);
  forth_request_free_prog (E);
  assert (E->prog == NULL);
  tlist_insert (&without_output_free_list, E);
  hash_req_remove (E);
}