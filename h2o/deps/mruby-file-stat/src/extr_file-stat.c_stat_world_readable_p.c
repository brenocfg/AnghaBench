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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int S_IROTH ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 struct stat* get_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
stat_world_readable_p(mrb_state *mrb, mrb_value self)
{
#ifdef S_IROTH
  struct stat *st = get_stat(mrb, self);
  if ((st->st_mode & (S_IROTH)) == S_IROTH) {
    return mrb_fixnum_value(st->st_mode & (S_IRUGO|S_IWUGO|S_IXUGO));
  }
  else {
    return mrb_nil_value();
  }
#else
  return mrb_nil_value();
#endif
}