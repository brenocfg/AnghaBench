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
typedef  int /*<<< orphan*/  xcb_char2b_t ;
struct TYPE_3__ {size_t num_glyphs; scalar_t__ num_bytes; int /*<<< orphan*/ * utf8; void* ucs2; } ;
typedef  TYPE_1__ i3String ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,size_t) ; 
 void* scalloc (size_t,int) ; 

i3String *i3string_from_ucs2(const xcb_char2b_t *from_ucs2, size_t num_glyphs) {
    i3String *str = scalloc(1, sizeof(i3String));

    /* Copy the actual text to our i3String */
    str->ucs2 = scalloc(num_glyphs, sizeof(xcb_char2b_t));
    memcpy(str->ucs2, from_ucs2, num_glyphs * sizeof(xcb_char2b_t));

    /* Store the length */
    str->num_glyphs = num_glyphs;

    str->utf8 = NULL;
    str->num_bytes = 0;

    return str;
}