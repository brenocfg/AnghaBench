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
typedef  size_t uint8_t ;
struct TYPE_3__ {int flags; size_t state; int /*<<< orphan*/  sym; } ;
typedef  TYPE_1__ nghttp2_huff_decode ;

/* Variables and functions */
 int NGHTTP2_HUFF_ACCEPTED ; 
 int NGHTTP2_HUFF_FAIL ; 
 size_t NGHTTP2_HUFF_INVALID_CHARS ; 
 int NGHTTP2_HUFF_SYM ; 
 TYPE_1__** huff_decode_table ; 

__attribute__((used)) static char *huffdecode4(char *dst, uint8_t in, uint8_t *state, int *maybe_eos, uint8_t *seen_char_types)
{
    const nghttp2_huff_decode *entry = huff_decode_table[*state] + in;

    if ((entry->flags & NGHTTP2_HUFF_FAIL) != 0)
        return NULL;
    if ((entry->flags & NGHTTP2_HUFF_SYM) != 0) {
        *dst++ = entry->sym;
        *seen_char_types |= (entry->flags & NGHTTP2_HUFF_INVALID_CHARS);
    }
    *state = entry->state;
    *maybe_eos = (entry->flags & NGHTTP2_HUFF_ACCEPTED) != 0;

    return dst;
}