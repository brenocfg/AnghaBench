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

/* Variables and functions */
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_is_top_num(struct jv_parser* p) {
  return (p->stackpos == 0 && jv_get_kind(p->next) == JV_KIND_NUMBER);
}