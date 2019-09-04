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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_false_value () ; 

mrb_value
mrb_filetest_s_pipe_p(mrb_state *mrb, mrb_value klass)
{
#if defined(_WIN32) || defined(_WIN64)
  mrb_raise(mrb, E_NOTIMP_ERROR, "pipe is not supported on this platform");
#else
#ifdef S_IFIFO
#  ifndef S_ISFIFO
#    define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#  endif

  struct stat st;
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);

  if (mrb_stat(mrb, obj, &st) < 0)
    return mrb_false_value();
  if (S_ISFIFO(st.st_mode))
    return mrb_true_value();

#endif
  return mrb_false_value();
#endif
}