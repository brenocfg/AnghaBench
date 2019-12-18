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
struct tm {int dummy; } ;
struct mrb_time {scalar_t__ timezone; struct tm datetime; scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 scalar_t__ MRB_TIMEZONE_UTC ; 
 struct tm* gmtime_r (scalar_t__*,struct tm*) ; 
 struct tm* localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mrb_time*
time_update_datetime(mrb_state *mrb, struct mrb_time *self)
{
  struct tm *aid;

  if (self->timezone == MRB_TIMEZONE_UTC) {
    aid = gmtime_r(&self->sec, &self->datetime);
  }
  else {
    aid = localtime_r(&self->sec, &self->datetime);
  }
  if (!aid) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "%S out of Time range", mrb_float_value(mrb, (mrb_float)self->sec));
    /* not reached */
    return NULL;
  }
#ifdef NO_GMTIME_R
  self->datetime = *aid; /* copy data */
#endif

  return self;
}