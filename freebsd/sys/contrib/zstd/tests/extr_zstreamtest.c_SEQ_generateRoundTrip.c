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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int /*<<< orphan*/  XXH64_state_t ;
struct TYPE_3__ {int member_1; int /*<<< orphan*/  pos; int /*<<< orphan*/  dst; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  SEQ_stream ;
typedef  TYPE_1__ SEQ_outBuffer ;
typedef  int /*<<< orphan*/  SEQ_gen_type ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t SEQ_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,TYPE_1__*) ; 
 size_t SEQ_roundTrip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_e_continue ; 
 scalar_t__ ZSTD_isError (size_t) ; 

__attribute__((used)) static size_t SEQ_generateRoundTrip(ZSTD_CCtx* cctx, ZSTD_DCtx* dctx,
                                    XXH64_state_t* xxh, SEQ_stream* seq,
                                    SEQ_gen_type type, unsigned value)
{
    static BYTE data[1024];
    size_t gen;

    do {
        SEQ_outBuffer sout = {data, sizeof(data), 0};
        size_t ret;
        gen = SEQ_gen(seq, type, value, &sout);

        ret = SEQ_roundTrip(cctx, dctx, xxh, sout.dst, sout.pos, ZSTD_e_continue);
        if (ZSTD_isError(ret))
            return ret;
    } while (gen != 0);

    return 0;
}