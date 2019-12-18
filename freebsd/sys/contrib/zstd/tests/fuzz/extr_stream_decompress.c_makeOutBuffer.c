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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 scalar_t__ FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ kBufSize ; 

__attribute__((used)) static ZSTD_outBuffer makeOutBuffer(FUZZ_dataProducer_t *producer)
{
  ZSTD_outBuffer buffer = { buf, 0, 0 };

  buffer.size = (FUZZ_dataProducer_uint32Range(producer, 1, kBufSize));
  FUZZ_ASSERT(buffer.size <= kBufSize);

  return buffer;
}