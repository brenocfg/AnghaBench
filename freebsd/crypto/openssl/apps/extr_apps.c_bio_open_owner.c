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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_CLOSE ; 
 int BIO_FP_TEXT ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int _O_BINARY ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,int /*<<< orphan*/ ) ; 
 int istext (int) ; 
 int /*<<< orphan*/  modestr (char,int) ; 
 int open (char const*,int,int,...) ; 
 int /*<<< orphan*/  opt_getprog () ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

BIO *bio_open_owner(const char *filename, int format, int private)
{
    FILE *fp = NULL;
    BIO *b = NULL;
    int fd = -1, bflags, mode, textmode;

    if (!private || filename == NULL || strcmp(filename, "-") == 0)
        return bio_open_default(filename, 'w', format);

    mode = O_WRONLY;
#ifdef O_CREAT
    mode |= O_CREAT;
#endif
#ifdef O_TRUNC
    mode |= O_TRUNC;
#endif
    textmode = istext(format);
    if (!textmode) {
#ifdef O_BINARY
        mode |= O_BINARY;
#elif defined(_O_BINARY)
        mode |= _O_BINARY;
#endif
    }

#ifdef OPENSSL_SYS_VMS
    /* VMS doesn't have O_BINARY, it just doesn't make sense.  But,
     * it still needs to know that we're going binary, or fdopen()
     * will fail with "invalid argument"...  so we tell VMS what the
     * context is.
     */
    if (!textmode)
        fd = open(filename, mode, 0600, "ctx=bin");
    else
#endif
        fd = open(filename, mode, 0600);
    if (fd < 0)
        goto err;
    fp = fdopen(fd, modestr('w', format));
    if (fp == NULL)
        goto err;
    bflags = BIO_CLOSE;
    if (textmode)
        bflags |= BIO_FP_TEXT;
    b = BIO_new_fp(fp, bflags);
    if (b)
        return b;

 err:
    BIO_printf(bio_err, "%s: Can't open \"%s\" for writing, %s\n",
               opt_getprog(), filename, strerror(errno));
    ERR_print_errors(bio_err);
    /* If we have fp, then fdopen took over fd, so don't close both. */
    if (fp)
        fclose(fp);
    else if (fd >= 0)
        close(fd);
    return NULL;
}