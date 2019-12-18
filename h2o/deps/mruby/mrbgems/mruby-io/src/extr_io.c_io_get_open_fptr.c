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
struct mrb_io {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_IO_ERROR ; 
 scalar_t__ mrb_get_datatype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_io_type ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct mrb_io *
io_get_open_fptr(mrb_state *mrb, mrb_value self)
{
  struct mrb_io *fptr;

  fptr = (struct mrb_io *)mrb_get_datatype(mrb, self, &mrb_io_type);
  if (fptr == NULL) {
    mrb_raise(mrb, E_IO_ERROR, "uninitialized stream.");
  }
  if (fptr->fd < 0) {
    mrb_raise(mrb, E_IO_ERROR, "closed stream.");
  }
  return fptr;
}