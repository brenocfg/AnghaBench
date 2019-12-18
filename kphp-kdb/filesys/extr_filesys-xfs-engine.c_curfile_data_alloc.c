#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  new_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; TYPE_1__ E; int /*<<< orphan*/  mrk; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_curfile_data_ptr ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__ curfile ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmalloc (unsigned int) ; 

__attribute__((used)) static void curfile_data_alloc (unsigned parts) {
  dyn_mark (curfile.mrk);
  unsigned size = parts << 16;
  if (size > 0x1000000) {
    curfile.data = allocated_curfile_data_ptr = malloc (curfile.E.new_size);
    assert (curfile.data);
  } else {
    curfile.data = zmalloc (size);
  }
}