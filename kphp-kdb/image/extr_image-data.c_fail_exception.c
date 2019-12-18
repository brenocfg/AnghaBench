#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct forth_stack {int dummy; } ;
struct TYPE_3__ {scalar_t__ severity; int /*<<< orphan*/  description; int /*<<< orphan*/  reason; } ;
typedef  TYPE_1__ ExceptionInfo ;

/* Variables and functions */
 scalar_t__ UndefinedException ; 
 int /*<<< orphan*/  failf (struct forth_stack*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fail_exception (struct forth_stack *st, ExceptionInfo *e_info) {
  if (e_info->severity != UndefinedException) {
    failf (st, "Magick: %s (%s).", e_info->reason, e_info->description);
  }
}