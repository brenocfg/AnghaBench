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
typedef  scalar_t__ char_type ;
struct TYPE_3__ {scalar_t__* cc_idx; scalar_t__ ch; } ;
typedef  TYPE_1__ CPUCell ;

/* Variables and functions */
 unsigned int arraysz (scalar_t__*) ; 
 scalar_t__ codepoint_for_mark (scalar_t__) ; 
 size_t encode_utf8 (scalar_t__,char*) ; 

size_t
cell_as_utf8(CPUCell *cell, bool include_cc, char *buf, char_type zero_char) {
    size_t n = encode_utf8(cell->ch ? cell->ch : zero_char, buf);
    if (include_cc) {
        for (unsigned i = 0; i < arraysz(cell->cc_idx) && cell->cc_idx[i]; i++) n += encode_utf8(codepoint_for_mark(cell->cc_idx[i]), buf + n);
    }
    buf[n] = 0;
    return n;
}