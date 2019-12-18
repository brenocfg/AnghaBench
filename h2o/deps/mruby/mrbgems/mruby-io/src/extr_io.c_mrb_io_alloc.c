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
struct mrb_io {int fd; int fd2; scalar_t__ is_socket; scalar_t__ sync; scalar_t__ writable; scalar_t__ readable; scalar_t__ pid; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct mrb_io *
mrb_io_alloc(mrb_state *mrb)
{
  struct mrb_io *fptr;

  fptr = (struct mrb_io *)mrb_malloc(mrb, sizeof(struct mrb_io));
  fptr->fd = -1;
  fptr->fd2 = -1;
  fptr->pid = 0;
  fptr->readable = 0;
  fptr->writable = 0;
  fptr->sync = 0;
  fptr->is_socket = 0;
  return fptr;
}