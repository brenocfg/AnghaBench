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
typedef  int flags_t ;

/* Variables and functions */
 int FLAGS_SIMPLIFY_FULL ; 
 int FLAGS_SIMPLIFY_PARTIAL ; 
 int SIMPLIFY_TYPE_FULL ; 
 int SIMPLIFY_TYPE_NONE ; 
 int SIMPLIFY_TYPE_PARTIAL ; 

__attribute__((used)) static int get_simplify_type ( flags_t flags ) {
  if (flags & FLAGS_SIMPLIFY_FULL)
    return SIMPLIFY_TYPE_FULL;
  if (flags & FLAGS_SIMPLIFY_PARTIAL)
    return SIMPLIFY_TYPE_PARTIAL;
  return SIMPLIFY_TYPE_NONE;
}