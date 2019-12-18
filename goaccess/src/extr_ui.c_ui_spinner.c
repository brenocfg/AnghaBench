#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_10__ {scalar_t__ no_progress; } ;
struct TYPE_9__ {TYPE_1__* pair; } ;
struct TYPE_8__ {scalar_t__ state; long long* processed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  win; int /*<<< orphan*/  spin_x; int /*<<< orphan*/  y; TYPE_3__* (* color ) () ;int /*<<< orphan*/  w; int /*<<< orphan*/  x; scalar_t__ curses; int /*<<< orphan*/  label; } ;
struct TYPE_7__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ GSpinner ;
typedef  TYPE_3__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 char* SPIN_FMT ; 
 char* SPIN_FMTM ; 
 int SPIN_LBL ; 
 int /*<<< orphan*/  SPIN_UPDATE_INTERVAL ; 
 scalar_t__ SPN_END ; 
 TYPE_6__ conf ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__* (*) ()) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_3__* stub1 () ; 
 scalar_t__ time (scalar_t__*) ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ui_spinner (void *ptr_data)
{
  GSpinner *sp = (GSpinner *) ptr_data;
  GColors *color = NULL;

  static char const spin_chars[] = "/-\\|";
  char buf[SPIN_LBL];
  int i = 0;
  long long tdiff = 0, psec = 0;
  time_t begin;

  if (sp->curses)
    color = (*sp->color) ();

  time (&begin);
  while (1) {
    pthread_mutex_lock (&sp->mutex);
    if (sp->state == SPN_END) {
      if (!sp->curses && !conf.no_progress)
        fprintf(stderr, "\n");

      break;
    }

    setlocale (LC_NUMERIC, "");
    if (conf.no_progress) {
      snprintf (buf, sizeof buf, SPIN_FMT, sp->label);
    } else {
      tdiff = (long long) (time (NULL) - begin);
      psec = tdiff >= 1 ? *(sp->processed) / tdiff : 0;
      snprintf (buf, sizeof buf, SPIN_FMTM, sp->label, *(sp->processed), psec);
    }
    setlocale (LC_NUMERIC, "POSIX");

    if (sp->curses) {
      /* CURSES */
      draw_header (sp->win, buf, " %s", sp->y, sp->x, sp->w, sp->color);
      /* caret */
      wattron (sp->win, COLOR_PAIR (color->pair->idx));
      mvwaddch (sp->win, sp->y, sp->spin_x, spin_chars[i++ & 3]);
      wattroff (sp->win, COLOR_PAIR (color->pair->idx));
      wrefresh (sp->win);
    } else if (!conf.no_progress) {
      /* STDOUT */
      fprintf (stderr, "%s\r", buf);
    }

    pthread_mutex_unlock (&sp->mutex);
    usleep (SPIN_UPDATE_INTERVAL);
  }
}