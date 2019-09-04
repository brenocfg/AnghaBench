#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  uahash; int /*<<< orphan*/  ip; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int type; int /*<<< orphan*/  str; TYPE_1__ p; } ;
typedef  TYPE_2__ lev_antispam_add_pattern_v1_t ;
typedef  int /*<<< orphan*/  flags_t ;
struct TYPE_8__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ antispam_pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_SIMPLIFY_FULL ; 
 int /*<<< orphan*/  FLAGS_SIMPLIFY_PARTIAL ; 
 int SIMPLIFY_TYPE_FULL ; 
 int SIMPLIFY_TYPE_PARTIAL ; 
 int add_pattern (TYPE_3__,int,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static bool add_pattern_v1 (lev_antispam_add_pattern_v1_t* E, bool replace) {
  flags_t flags = 0; /* SIMPLIFY_TYPE_NONE */
  E->p.flags &= 3;
  if (E->p.flags == SIMPLIFY_TYPE_PARTIAL) {
    flags |= FLAGS_SIMPLIFY_PARTIAL;
  } else if (E->p.flags == SIMPLIFY_TYPE_FULL) {
    flags |= FLAGS_SIMPLIFY_FULL;
  }
  antispam_pattern_t pattern = {E->p.id, E->p.ip, E->p.uahash, flags};
  return add_pattern (pattern, (E->type & 0xFFFF), E->str, replace, "v1");
}