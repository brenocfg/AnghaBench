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
struct process_id {int dummy; } ;
typedef  enum tl_type { ____Placeholder_tl_type } tl_type ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_UNKNOWN ; 
 int /*<<< orphan*/  tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tl_init_store_keep_error (int,struct process_id*,long long) ; 
 int /*<<< orphan*/  tl_store_end () ; 

void _fail_query (enum tl_type type, struct process_id *PID, long long qid) {
  if (PID) {
    if (tl_init_store_keep_error (type, PID, qid) >= 0) {
      if (!tl_fetch_error ()) {
        tl_fetch_set_error ("Unknown error", TL_ERROR_UNKNOWN);
      }
      tl_store_end ();
    }
  }
}