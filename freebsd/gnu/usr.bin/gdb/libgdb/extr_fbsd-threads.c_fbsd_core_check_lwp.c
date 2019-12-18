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
typedef  scalar_t__ lwpid_t ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 scalar_t__ atoi (scalar_t__) ; 
 scalar_t__ bfd_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void
fbsd_core_check_lwp (bfd *abfd, asection *asect, void *obj)
{
  lwpid_t lwp;

  if (strncmp (bfd_section_name (abfd, asect), ".reg/", 5) != 0)
    return;

  /* already found */
  if (*(lwpid_t *)obj == 0)
    return;

  lwp = atoi (bfd_section_name (abfd, asect) + 5);
  if (*(lwpid_t *)obj == lwp)
    *(lwpid_t *)obj = 0;
}