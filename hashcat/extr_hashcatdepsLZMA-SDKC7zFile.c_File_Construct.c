#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ CSzFile ;

/* Variables and functions */

void File_Construct(CSzFile *p)
{
  #ifdef USE_WINDOWS_FILE
  p->handle = INVALID_HANDLE_VALUE;
  #else
  p->file = NULL;
  #endif
}