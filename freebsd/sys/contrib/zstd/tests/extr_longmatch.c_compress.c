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
typedef  int /*<<< orphan*/  ZSTD_outBuffer ;
struct TYPE_3__ {void const* member_0; size_t member_1; scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_CStream ;

/* Variables and functions */
 size_t ZSTD_compressStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t ZSTD_flushStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 

__attribute__((used)) static int
compress(ZSTD_CStream *ctx, ZSTD_outBuffer out, const void *data, size_t size)
{
  ZSTD_inBuffer in = { data, size, 0 };
  while (in.pos < in.size) {
    ZSTD_outBuffer tmp = out;
    const size_t rc = ZSTD_compressStream(ctx, &tmp, &in);
    if (ZSTD_isError(rc)) return 1;
  }
  { ZSTD_outBuffer tmp = out;
    const size_t rc = ZSTD_flushStream(ctx, &tmp);
    if (rc != 0) { return 1; }
  }
  return 0;
}