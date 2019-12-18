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
struct thread_info {int /*<<< orphan*/  ptid; int /*<<< orphan*/  num; struct thread_info* next; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  error (char*) ; 
 struct frame_info* find_relative_frame (int /*<<< orphan*/ ,int*) ; 
 int frame_relative_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_selected_frame () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ legacy_frame_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  prune_threads () ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int /*<<< orphan*/  show_stack_frame (struct frame_info*) ; 
 int /*<<< orphan*/  switch_to_thread (int /*<<< orphan*/ ) ; 
 char* target_extra_thread_info (struct thread_info*) ; 
 int /*<<< orphan*/  target_find_new_threads () ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_tid_to_str (int /*<<< orphan*/ ) ; 
 struct thread_info* thread_list ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
info_threads_command (char *arg, int from_tty)
{
  struct thread_info *tp;
  ptid_t current_ptid;
  struct frame_info *cur_frame;
  int saved_frame_level = frame_relative_level (get_selected_frame ());
  int counter;
  char *extra_info;

  /* Check that there really is a frame.  This happens when a simulator
     is connected but not loaded or running, for instance.  */
  if (legacy_frame_p (current_gdbarch) && saved_frame_level < 0)
    error ("No frame.");

  prune_threads ();
  target_find_new_threads ();
  current_ptid = inferior_ptid;
  for (tp = thread_list; tp; tp = tp->next)
    {
      if (ptid_equal (tp->ptid, current_ptid))
	printf_filtered ("* ");
      else
	printf_filtered ("  ");

#ifdef HPUXHPPA
      printf_filtered ("%d %s", tp->num, target_tid_to_str (tp->ptid));
#else
      printf_filtered ("%d %s", tp->num, target_pid_to_str (tp->ptid));
#endif

      extra_info = target_extra_thread_info (tp);
      if (extra_info)
	printf_filtered (" (%s)", extra_info);
      puts_filtered ("  ");

      switch_to_thread (tp->ptid);
      print_stack_frame (get_selected_frame (), -1, 0);
    }

  switch_to_thread (current_ptid);

  /* Code below copied from "up_silently_base" in "stack.c".
   * It restores the frame set by the user before the "info threads"
   * command.  We have finished the info-threads display by switching
   * back to the current thread.  That switch has put us at the top
   * of the stack (leaf frame).
   */
  counter = saved_frame_level;
  cur_frame = find_relative_frame (get_selected_frame (), &counter);
  if (counter != 0)
    {
      /* Ooops, can't restore, tell user where we are. */
      warning ("Couldn't restore frame in current thread, at frame 0");
      print_stack_frame (get_selected_frame (), -1, 0);
    }
  else
    {
      select_frame (cur_frame);
    }

  /* re-show current frame. */
  show_stack_frame (cur_frame);
}