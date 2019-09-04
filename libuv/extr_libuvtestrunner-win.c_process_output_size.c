#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stdio_out; } ;
typedef  TYPE_1__ process_info_t ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  GetFileSizeEx (int /*<<< orphan*/ ,TYPE_2__*) ; 

long int process_output_size(process_info_t *p) {
  LARGE_INTEGER size;
  if (!GetFileSizeEx(p->stdio_out, &size))
    return -1;
  return (long int)size.QuadPart;
}