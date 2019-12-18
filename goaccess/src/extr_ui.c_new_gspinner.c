#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int no_progress; scalar_t__ load_from_disk; } ;
struct TYPE_5__ {char* label; int /*<<< orphan*/  mutex; scalar_t__ curses; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ GSpinner ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  SPN_RUN ; 
 TYPE_4__ conf ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* xcalloc (int,int) ; 

GSpinner *
new_gspinner (void)
{
  GSpinner *spinner;

  spinner = xcalloc (1, sizeof (GSpinner));
  spinner->label = "Parsing...";
  spinner->state = SPN_RUN;
  spinner->curses = 0;
  if (conf.load_from_disk)
    conf.no_progress = 1;

  if (pthread_mutex_init (&(spinner->mutex), NULL))
    FATAL ("Failed init thread mutex");

  return spinner;
}