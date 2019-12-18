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
struct TYPE_2__ {scalar_t__ major; int minorFrom; } ;
typedef  TYPE_1__ TtyDriver ;

/* Variables and functions */

__attribute__((used)) static int sortTtyDrivers(const void* va, const void* vb) {
   TtyDriver* a = (TtyDriver*) va;
   TtyDriver* b = (TtyDriver*) vb;
   return (a->major == b->major) ? (a->minorFrom - b->minorFrom) : (a->major - b->major);
}