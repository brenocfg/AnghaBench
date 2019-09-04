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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  MRB_TT_CLASS 134 
#define  MRB_TT_DATA 133 
#define  MRB_TT_EXCEPTION 132 
#define  MRB_TT_HASH 131 
#define  MRB_TT_MODULE 130 
#define  MRB_TT_OBJECT 129 
#define  MRB_TT_SCLASS 128 
 int /*<<< orphan*/  TRUE ; 
 int mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
obj_iv_p(mrb_value obj)
{
  switch (mrb_type(obj)) {
    case MRB_TT_OBJECT:
    case MRB_TT_CLASS:
    case MRB_TT_MODULE:
    case MRB_TT_SCLASS:
    case MRB_TT_HASH:
    case MRB_TT_DATA:
    case MRB_TT_EXCEPTION:
      return TRUE;
    default:
      return FALSE;
  }
}