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
struct stat {scalar_t__ st_uid; int st_mode; int /*<<< orphan*/  st_gid; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 struct stat* get_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 scalar_t__ mrb_group_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
stat_writable_real_p(mrb_state *mrb, mrb_value self)
{
  struct stat *st;

#ifdef USE_GETEUID
  if (getuid() == 0)
    return mrb_true_value();
#endif
  st = get_stat(mrb, self);
#ifdef S_IWUSR
  if (st->st_uid == getuid())
    return st->st_mode & S_IWUSR ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IWGRP
  if (mrb_group_member(mrb, st->st_gid))
    return st->st_mode & S_IWGRP ? mrb_true_value() : mrb_false_value();
#endif
#ifdef S_IWOTH
  if (!(st->st_mode & S_IWOTH)) return mrb_false_value();
#endif
  return mrb_true_value();
}