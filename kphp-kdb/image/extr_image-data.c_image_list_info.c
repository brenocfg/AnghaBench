#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ severity; } ;
typedef  TYPE_1__ ExceptionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CatchException (TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyExceptionInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  GetExceptionInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  ListMagickInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ UndefinedException ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

void image_list_info (void) {
  if (verbosity > 0) {
    ExceptionInfo exception;
    GetExceptionInfo (&exception);
    ListMagickInfo (stderr, &exception);
    if (exception.severity != UndefinedException) {
      CatchException (&exception);
    }
    DestroyExceptionInfo (&exception);
  }
}