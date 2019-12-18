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
typedef  int /*<<< orphan*/  xcb_key_symbols_t ;
typedef  int /*<<< orphan*/  xcb_get_modifier_mapping_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_modifier_mapping_cookie_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mod_mask_for (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_get_modifier_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_get_modifier_mapping_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint32_t aio_get_mod_mask_for(uint32_t keysym, xcb_key_symbols_t *symbols) {
    xcb_get_modifier_mapping_cookie_t cookie;
    xcb_get_modifier_mapping_reply_t *modmap_r;

    xcb_flush(conn);

    /* Get the current modifier mapping (this is blocking!) */
    cookie = xcb_get_modifier_mapping(conn);
    if (!(modmap_r = xcb_get_modifier_mapping_reply(conn, cookie, NULL)))
        return 0;

    uint32_t result = get_mod_mask_for(keysym, symbols, modmap_r);
    free(modmap_r);
    return result;
}