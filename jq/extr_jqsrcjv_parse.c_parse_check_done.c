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
struct jv_parser {scalar_t__ stackpos; int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_invalid () ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_check_done(struct jv_parser* p, jv* out) {
  if (p->stackpos == 0 && jv_is_valid(p->next)) {
    *out = p->next;
    p->next = jv_invalid();
    return 1;
  } else {
    return 0;
  }
}