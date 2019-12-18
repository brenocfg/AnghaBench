#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mrk; } ;

/* Variables and functions */
 int /*<<< orphan*/ * allocated_curfile_data_ptr ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void curfile_data_free (int release) {
  if (release) {
    dyn_release (curfile.mrk);
  }
  if (allocated_curfile_data_ptr != NULL) {
    free (allocated_curfile_data_ptr);
    allocated_curfile_data_ptr = NULL;
  }
}