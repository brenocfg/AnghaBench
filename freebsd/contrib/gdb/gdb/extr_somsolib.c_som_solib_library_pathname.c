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
struct som_solib_mapped_entry {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  dll_descriptor ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARG1_REGNUM ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int) ; 
 scalar_t__ read_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
som_solib_library_pathname (int pid)
{
  CORE_ADDR dll_handle_address;
  CORE_ADDR dll_pathname_address;
  struct som_solib_mapped_entry dll_descriptor;
  char *p;
  static char dll_pathname[1024];

  /* Read the descriptor of this newly-loaded library. */
  dll_handle_address = read_register (ARG1_REGNUM);
  read_memory (dll_handle_address, (char *) &dll_descriptor, sizeof (dll_descriptor));

  /* We can find a pointer to the dll's pathname within the descriptor. */
  dll_pathname_address = (CORE_ADDR) dll_descriptor.name;

  /* Read the pathname, one byte at a time. */
  p = dll_pathname;
  for (;;)
    {
      char b;
      read_memory (dll_pathname_address++, (char *) &b, 1);
      *p++ = b;
      if (b == '\0')
	break;
    }

  return dll_pathname;
}