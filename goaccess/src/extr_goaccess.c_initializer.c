#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  current; } ;
struct TYPE_8__ {int /*<<< orphan*/ * processed; } ;
struct TYPE_7__ {int /*<<< orphan*/  processed; } ;

/* Variables and functions */
 TYPE_1__* glog ; 
 TYPE_5__ gscroll ; 
 int /*<<< orphan*/  init_geoip () ; 
 TYPE_1__* init_log () ; 
 int /*<<< orphan*/  init_modules () ; 
 TYPE_2__* new_gspinner () ; 
 int /*<<< orphan*/  parse_browsers_file () ; 
 TYPE_2__* parsing_spinner ; 
 int /*<<< orphan*/  set_io () ; 
 int /*<<< orphan*/  set_locale () ; 
 int /*<<< orphan*/  set_signal_data (TYPE_1__*) ; 

__attribute__((used)) static void
initializer (void)
{
  /* initialize modules and set first */
  gscroll.current = init_modules ();
  /* setup to use the current locale */
  set_locale ();

  parse_browsers_file ();

#ifdef HAVE_GEOLOCATION
  init_geoip ();
#endif

  /* init glog */
  glog = init_log ();

  set_io ();
  set_signal_data (glog);

  /* init parsing spinner */
  parsing_spinner = new_gspinner ();
  parsing_spinner->processed = &glog->processed;
}