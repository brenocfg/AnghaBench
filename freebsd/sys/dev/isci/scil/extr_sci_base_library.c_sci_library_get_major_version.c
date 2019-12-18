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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  __SCI_LIBRARY_MAJOR_VERSION__ ; 

U32 sci_library_get_major_version(
   void
)
{
   // Return the 32-bit value representing the major version for this SCI
   // binary.
   return __SCI_LIBRARY_MAJOR_VERSION__;
}