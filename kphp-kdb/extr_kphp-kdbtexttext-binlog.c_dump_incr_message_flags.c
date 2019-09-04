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
struct lev_generic {int type; int a; int b; } ;

/* Variables and functions */
 scalar_t__ dump_line_header (char*,char) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static void dump_incr_message_flags (struct lev_generic *E) {
  if (dump_line_header ("LEV_TX_INCR_MESSAGE_FLAGS", '+') < 0) {
    return; 
  }
  fprintf (out, "%d\t%d\t%d\n", E->type & 0xff, E->a, E->b);
}