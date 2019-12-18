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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int ENGINE_CMD_FLAG_INTERNAL ; 
 unsigned int ENGINE_CMD_FLAG_NO_INPUT ; 
 unsigned int ENGINE_CMD_FLAG_NUMERIC ; 
 unsigned int ENGINE_CMD_FLAG_STRING ; 

__attribute__((used)) static int util_flags(BIO *out, unsigned int flags, const char *indent)
{
    int started = 0, err = 0;
    /* Indent before displaying input flags */
    BIO_printf(out, "%s%s(input flags): ", indent, indent);
    if (flags == 0) {
        BIO_printf(out, "<no flags>\n");
        return 1;
    }
    /*
     * If the object is internal, mark it in a way that shows instead of
     * having it part of all the other flags, even if it really is.
     */
    if (flags & ENGINE_CMD_FLAG_INTERNAL) {
        BIO_printf(out, "[Internal] ");
    }

    if (flags & ENGINE_CMD_FLAG_NUMERIC) {
        BIO_printf(out, "NUMERIC");
        started = 1;
    }
    /*
     * Now we check that no combinations of the mutually exclusive NUMERIC,
     * STRING, and NO_INPUT flags have been used. Future flags that can be
     * OR'd together with these would need to added after these to preserve
     * the testing logic.
     */
    if (flags & ENGINE_CMD_FLAG_STRING) {
        if (started) {
            BIO_printf(out, "|");
            err = 1;
        }
        BIO_printf(out, "STRING");
        started = 1;
    }
    if (flags & ENGINE_CMD_FLAG_NO_INPUT) {
        if (started) {
            BIO_printf(out, "|");
            err = 1;
        }
        BIO_printf(out, "NO_INPUT");
        started = 1;
    }
    /* Check for unknown flags */
    flags = flags & ~ENGINE_CMD_FLAG_NUMERIC &
        ~ENGINE_CMD_FLAG_STRING &
        ~ENGINE_CMD_FLAG_NO_INPUT & ~ENGINE_CMD_FLAG_INTERNAL;
    if (flags) {
        if (started)
            BIO_printf(out, "|");
        BIO_printf(out, "<0x%04X>", flags);
    }
    if (err)
        BIO_printf(out, "  <illegal flags!>");
    BIO_printf(out, "\n");
    return 1;
}