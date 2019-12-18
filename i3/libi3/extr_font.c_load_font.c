#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
typedef  int /*<<< orphan*/  xcb_query_font_cookie_t ;
struct TYPE_14__ {char const* error_code; } ;
typedef  TYPE_3__ xcb_generic_error_t ;
struct TYPE_12__ {TYPE_6__* info; int /*<<< orphan*/ * table; int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_1__ xcb; } ;
struct TYPE_15__ {int /*<<< orphan*/  type; TYPE_2__ specific; scalar_t__ height; int /*<<< orphan*/ * pattern; } ;
typedef  TYPE_4__ i3Font ;
struct TYPE_16__ {scalar_t__ font_descent; scalar_t__ font_ascent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,...) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FONT_TYPE_NONE ; 
 int /*<<< orphan*/  FONT_TYPE_XCB ; 
 int /*<<< orphan*/  LOG (char*,char const*) ; 
 int /*<<< orphan*/ * conn ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  free_font () ; 
 scalar_t__ load_pango_font (TYPE_4__*,char const*) ; 
 void* sstrdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  xcb_generate_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_open_font_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  xcb_query_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_query_font_char_infos (TYPE_6__*) ; 
 scalar_t__ xcb_query_font_char_infos_length (TYPE_6__*) ; 
 TYPE_6__* xcb_query_font_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* xcb_request_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

i3Font load_font(const char *pattern, const bool fallback) {
    /* if any font was previously loaded, free it now */
    free_font();

    i3Font font;
    font.type = FONT_TYPE_NONE;
    font.pattern = NULL;

    /* No XCB connction, return early because we're just validating the
     * configuration file. */
    if (conn == NULL) {
        return font;
    }

    /* Try to load a pango font if specified */
    if (strlen(pattern) > strlen("pango:") && !strncmp(pattern, "pango:", strlen("pango:"))) {
        const char *font_pattern = pattern + strlen("pango:");
        if (load_pango_font(&font, font_pattern)) {
            font.pattern = sstrdup(pattern);
            return font;
        }
    } else if (strlen(pattern) > strlen("xft:") && !strncmp(pattern, "xft:", strlen("xft:"))) {
        const char *font_pattern = pattern + strlen("xft:");
        if (load_pango_font(&font, font_pattern)) {
            font.pattern = sstrdup(pattern);
            return font;
        }
    }

    /* Send all our requests first */
    font.specific.xcb.id = xcb_generate_id(conn);
    xcb_void_cookie_t font_cookie = xcb_open_font_checked(conn, font.specific.xcb.id,
                                                          strlen(pattern), pattern);
    xcb_query_font_cookie_t info_cookie = xcb_query_font(conn, font.specific.xcb.id);

    /* Check for errors. If errors, fall back to default font. */
    xcb_generic_error_t *error;
    error = xcb_request_check(conn, font_cookie);

    /* If we fail to open font, fall back to 'fixed' */
    if (fallback && error != NULL) {
        ELOG("Could not open font %s (X error %d). Trying fallback to 'fixed'.\n",
             pattern, error->error_code);
        pattern = "fixed";
        font_cookie = xcb_open_font_checked(conn, font.specific.xcb.id,
                                            strlen(pattern), pattern);
        info_cookie = xcb_query_font(conn, font.specific.xcb.id);

        /* Check if we managed to open 'fixed' */
        free(error);
        error = xcb_request_check(conn, font_cookie);

        /* Fall back to '-misc-*' if opening 'fixed' fails. */
        if (error != NULL) {
            ELOG("Could not open fallback font 'fixed', trying with '-misc-*'.\n");
            pattern = "-misc-*";
            font_cookie = xcb_open_font_checked(conn, font.specific.xcb.id,
                                                strlen(pattern), pattern);
            info_cookie = xcb_query_font(conn, font.specific.xcb.id);

            free(error);
            if ((error = xcb_request_check(conn, font_cookie)) != NULL)
                errx(EXIT_FAILURE, "Could open neither requested font nor fallbacks "
                                   "(fixed or -misc-*): X11 error %d",
                     error->error_code);
        }
    }
    free(error);

    font.pattern = sstrdup(pattern);
    LOG("Using X font %s\n", pattern);

    /* Get information (height/name) for this font */
    if (!(font.specific.xcb.info = xcb_query_font_reply(conn, info_cookie, NULL)))
        errx(EXIT_FAILURE, "Could not load font \"%s\"", pattern);

    /* Get the font table, if possible */
    if (xcb_query_font_char_infos_length(font.specific.xcb.info) == 0)
        font.specific.xcb.table = NULL;
    else
        font.specific.xcb.table = xcb_query_font_char_infos(font.specific.xcb.info);

    /* Calculate the font height */
    font.height = font.specific.xcb.info->font_ascent + font.specific.xcb.info->font_descent;

    /* Set the font type and return successfully */
    font.type = FONT_TYPE_XCB;
    return font;
}