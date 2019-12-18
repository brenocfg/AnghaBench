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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 size_t FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,int,size_t) ; 

__attribute__((used)) static ZSTD_outBuffer makeOutBuffer(uint8_t *dst, size_t capacity,
                                    FUZZ_dataProducer_t *producer)
{
    ZSTD_outBuffer buffer = { dst, 0, 0 };

    FUZZ_ASSERT(capacity > 0);
    buffer.size = (FUZZ_dataProducer_uint32Range(producer, 1, capacity));
    FUZZ_ASSERT(buffer.size <= capacity);

    return buffer;
}