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
struct jv_parser {int flags; scalar_t__ stackpos; scalar_t__ tokenpos; int /*<<< orphan*/  next; int /*<<< orphan*/  last_ch_was_ws; } ;

/* Variables and functions */
 scalar_t__ JV_KIND_NUMBER ; 
 int JV_PARSE_SEQ ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_check_truncation(struct jv_parser* p) {
  return ((p->flags & JV_PARSE_SEQ) && !p->last_ch_was_ws && (p->stackpos > 0 || p->tokenpos > 0 || jv_get_kind(p->next) == JV_KIND_NUMBER));
}