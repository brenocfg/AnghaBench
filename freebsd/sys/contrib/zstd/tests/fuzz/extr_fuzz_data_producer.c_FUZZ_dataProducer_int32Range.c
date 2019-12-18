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
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 scalar_t__ FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

int32_t FUZZ_dataProducer_int32Range(FUZZ_dataProducer_t *producer,
                                    int32_t min, int32_t max)
{
    FUZZ_ASSERT(min <= max);

    if (min < 0)
      return (int)FUZZ_dataProducer_uint32Range(producer, 0, max - min) + min;

    return FUZZ_dataProducer_uint32Range(producer, min, max);
}