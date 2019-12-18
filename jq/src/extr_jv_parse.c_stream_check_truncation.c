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
struct jv_parser {scalar_t__ stacklen; int /*<<< orphan*/  next; } ;
typedef  scalar_t__ jv_kind ;

/* Variables and functions */
 scalar_t__ JV_KIND_FALSE ; 
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_TRUE ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stream_check_truncation(struct jv_parser* p) {
  jv_kind k = jv_get_kind(p->next);
  return (p->stacklen > 0 || k == JV_KIND_NUMBER || k == JV_KIND_TRUE || k == JV_KIND_FALSE || k == JV_KIND_NULL);
}