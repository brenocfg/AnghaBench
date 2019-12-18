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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {char* (* to_make_corefile_notes ) (int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 TYPE_1__ procfs_ops ; 
 char* stub1 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static char *
sol_make_note_section (bfd *obfd, int *note_size)
{
  return procfs_ops.to_make_corefile_notes (obfd, note_size);
}