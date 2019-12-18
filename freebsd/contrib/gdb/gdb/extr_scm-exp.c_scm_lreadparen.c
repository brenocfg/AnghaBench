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

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  lexptr ; 
 int /*<<< orphan*/  scm_lreadr (int) ; 
 int scm_skip_ws () ; 

__attribute__((used)) static void
scm_lreadparen (int skipping)
{
  for (;;)
    {
      int c = scm_skip_ws ();
      if (')' == c || ']' == c)
	return;
      --lexptr;
      if (c == '\0')
	error ("missing close paren");
      scm_lreadr (skipping);
    }
}