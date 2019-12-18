#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int min_byte1; int max_byte1; int min_char_or_byte2; int max_char_or_byte2; } ;
typedef  TYPE_3__ xcb_query_font_reply_t ;
struct TYPE_12__ {scalar_t__ character_width; int right_side_bearing; int left_side_bearing; int ascent; int descent; } ;
typedef  TYPE_4__ xcb_charinfo_t ;
struct TYPE_13__ {int byte1; int byte2; } ;
typedef  TYPE_5__ xcb_char2b_t ;
struct TYPE_9__ {TYPE_4__* table; TYPE_3__* info; } ;
struct TYPE_10__ {TYPE_1__ xcb; } ;
struct TYPE_14__ {TYPE_2__ specific; } ;

/* Variables and functions */
 TYPE_7__* savedFont ; 
 int xcb_query_text_width (TYPE_5__ const*,size_t) ; 

__attribute__((used)) static int predict_text_width_xcb(const xcb_char2b_t *input, size_t text_len) {
    if (text_len == 0)
        return 0;

    int width;
    if (savedFont->specific.xcb.table == NULL) {
        /* If we don't have a font table, fall back to querying the server */
        width = xcb_query_text_width(input, text_len);
    } else {
        /* Save some pointers for convenience */
        xcb_query_font_reply_t *font_info = savedFont->specific.xcb.info;
        xcb_charinfo_t *font_table = savedFont->specific.xcb.table;

        /* Calculate the width using the font table */
        width = 0;
        for (size_t i = 0; i < text_len; i++) {
            xcb_charinfo_t *info;
            int row = input[i].byte1;
            int col = input[i].byte2;

            if (row < font_info->min_byte1 ||
                row > font_info->max_byte1 ||
                col < font_info->min_char_or_byte2 ||
                col > font_info->max_char_or_byte2)
                continue;

            /* Don't you ask me, how this one works… (Merovius) */
            info = &font_table[((row - font_info->min_byte1) *
                                (font_info->max_char_or_byte2 - font_info->min_char_or_byte2 + 1)) +
                               (col - font_info->min_char_or_byte2)];

            if (info->character_width != 0 ||
                (info->right_side_bearing |
                 info->left_side_bearing |
                 info->ascent |
                 info->descent) != 0) {
                width += info->character_width;
            }
        }
    }

    return width;
}