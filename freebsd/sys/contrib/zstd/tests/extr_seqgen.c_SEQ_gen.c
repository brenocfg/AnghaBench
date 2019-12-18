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
typedef  int /*<<< orphan*/  SEQ_stream ;
typedef  int /*<<< orphan*/  SEQ_outBuffer ;
typedef  int SEQ_gen_type ;

/* Variables and functions */
 size_t SEQ_gen_litLength (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
#define  SEQ_gen_ll 131 
 size_t SEQ_gen_matchLength (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
#define  SEQ_gen_max 130 
#define  SEQ_gen_ml 129 
#define  SEQ_gen_of 128 
 size_t SEQ_gen_offset (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

size_t SEQ_gen(SEQ_stream* stream, SEQ_gen_type type, unsigned value, SEQ_outBuffer* out)
{
    switch (type) {
        case SEQ_gen_ml: return SEQ_gen_matchLength(stream, value, out);
        case SEQ_gen_ll: return SEQ_gen_litLength(stream, value, out);
        case SEQ_gen_of: return SEQ_gen_offset(stream, value, out);
        case SEQ_gen_max: /* fall-through */
        default: return 0;
    }
}