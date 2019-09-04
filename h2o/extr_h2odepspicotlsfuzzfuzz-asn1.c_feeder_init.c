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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t size; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 TYPE_1__ feeder ; 

__attribute__((used)) static void feeder_init(const uint8_t *orig_data, size_t orig_size)
{
    feeder.data = orig_data;
    feeder.size = orig_size;
}