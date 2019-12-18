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
typedef  int /*<<< orphan*/  mrb_bool ;
typedef  enum mrb_vtype { ____Placeholder_mrb_vtype } mrb_vtype ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MRB_TT_CLASS ; 
 int MRB_TT_MODULE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline mrb_bool
namespace_p(enum mrb_vtype tt)
{
  return tt == MRB_TT_CLASS || tt == MRB_TT_MODULE ? TRUE : FALSE;
}