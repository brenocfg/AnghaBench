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
 int /*<<< orphan*/ * BIO_new_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * dup_bio_in (int) ; 
 int /*<<< orphan*/ * dup_bio_out (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  modestr (char,int) ; 
 int /*<<< orphan*/  modeverb (char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BIO *bio_open_default_(const char *filename, char mode, int format,
                              int quiet)
{
    BIO *ret;

    if (filename == NULL || strcmp(filename, "-") == 0) {
        ret = mode == 'r' ? dup_bio_in(format) : dup_bio_out(format);
        if (quiet) {
            ERR_clear_error();
            return ret;
        }
        if (ret != NULL)
            return ret;
        BIO_printf(bio_err,
                   "Can't open %s, %s\n",
                   mode == 'r' ? "stdin" : "stdout", strerror(errno));
    } else {
        ret = BIO_new_file(filename, modestr(mode, format));
        if (quiet) {
            ERR_clear_error();
            return ret;
        }
        if (ret != NULL)
            return ret;
        BIO_printf(bio_err,
                   "Can't open %s for %s, %s\n",
                   filename, modeverb(mode), strerror(errno));
    }
    ERR_print_errors(bio_err);
    return NULL;
}