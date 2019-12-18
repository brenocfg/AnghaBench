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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 struct stat* get_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_static (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static mrb_value
stat_ftype(mrb_state *mrb, mrb_value self)
{
  struct stat *st = get_stat(mrb, self);
  const char *t;

  if (S_ISREG(st->st_mode)) {
    t = "file";
  }
  else if (S_ISDIR(st->st_mode)) {
    t = "directory";
  }
  else if (S_ISCHR(st->st_mode)) {
    t = "characterSpecial";
  }
#ifdef S_ISBLK
  else if (S_ISBLK(st->st_mode)) {
    t = "blockSpecial";
  }
#endif
#ifdef S_ISFIFO
  else if (S_ISFIFO(st->st_mode)) {
    t = "fifo";
  }
#endif
#ifdef S_ISLNK
  else if (S_ISLNK(st->st_mode)) {
    t = "link";
  }
#endif
#ifdef S_ISSOCK
  else if (S_ISSOCK(st->st_mode)) {
    t = "socket";
  }
#endif
  else {
    t = "unknown";
  }
  return mrb_str_new_static(mrb, t, (size_t)strlen(t));
}