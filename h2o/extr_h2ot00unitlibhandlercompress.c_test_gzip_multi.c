#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  inbufs ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* transform ) (TYPE_2__*,TYPE_1__*,int,int,TYPE_1__**,size_t*) ;} ;
typedef  TYPE_2__ h2o_compress_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  Z_BEST_SPEED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_result (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_2__* h2o_compress_gzip_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*,int,int,TYPE_1__**,size_t*) ; 

void test_gzip_multi(void)
{
#define P1                                                                                                                         \
    "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she "  \
    "had peeped into the book her sister was reading, but it had no pictures or conversations in it, `and what is the use of a "   \
    "book,' thought Alice `without pictures or conversation?'\n\n"
#define P2                                                                                                                         \
    "So she was considering in her own mind (as well as she could, for the hot day made her feel very sleepy and stupid), "        \
    "whether the pleasure of making a daisy-chain would be worth the trouble of getting up and picking the daisies, when "         \
    "suddenly a White Rabbit with pink eyes ran close by her.\n\n"
#define P3                                                                                                                         \
    "There was nothing so very remarkable in that; nor did Alice think it so very much out of the way to hear the Rabbit say to "  \
    "itself, `Oh dear! Oh dear! I shall be late!' (when she thought it over afterwards, it occurred to her that she ought to "     \
    "have wondered at this, but at the time it all seemed quite natural); but when the Rabbit actually took a watch out of its "   \
    "waistcoat-pocket, and looked at it, and then hurried on, Alice started to her feet, for it flashed across her mind that she " \
    "had never before seen a rabbit with either a waistcoat-pocket, or a watch to take out of it, and burning with curiosity, "    \
    "she ran across the field after it, and fortunately was just in time to see it pop down a large rabbit-hole under the "        \
    "hedge.\n\n"

    h2o_mem_pool_t pool;
    h2o_iovec_t inbufs[] = {{H2O_STRLIT(P1)}, {H2O_STRLIT(P2)}, {H2O_STRLIT(P3)}}, *outbufs;
    size_t outbufcnt;

    h2o_mem_init_pool(&pool);

    h2o_compress_context_t *compressor = h2o_compress_gzip_open(&pool, Z_BEST_SPEED);
    compressor->transform(compressor, inbufs, sizeof(inbufs) / sizeof(inbufs[0]), 1, &outbufs, &outbufcnt);

    assert(outbufcnt > 1); /* we want to test multi-vec output */

    check_result(outbufs, outbufcnt, H2O_STRLIT(P1 P2 P3));

    h2o_mem_clear_pool(&pool);

#undef P1
#undef P2
#undef P3
}