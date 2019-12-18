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
 int APP_PASS_LEN ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_fd (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FORMAT_TEXT ; 
 char* OPENSSL_strdup (char const*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * dup_bio_in (int /*<<< orphan*/ ) ; 
 char* getenv (char const*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static char *app_get_pass(const char *arg, int keepbio)
{
    char *tmp, tpass[APP_PASS_LEN];
    static BIO *pwdbio = NULL;
    int i;

    if (strncmp(arg, "pass:", 5) == 0)
        return OPENSSL_strdup(arg + 5);
    if (strncmp(arg, "env:", 4) == 0) {
        tmp = getenv(arg + 4);
        if (tmp == NULL) {
            BIO_printf(bio_err, "Can't read environment variable %s\n", arg + 4);
            return NULL;
        }
        return OPENSSL_strdup(tmp);
    }
    if (!keepbio || pwdbio == NULL) {
        if (strncmp(arg, "file:", 5) == 0) {
            pwdbio = BIO_new_file(arg + 5, "r");
            if (pwdbio == NULL) {
                BIO_printf(bio_err, "Can't open file %s\n", arg + 5);
                return NULL;
            }
#if !defined(_WIN32)
            /*
             * Under _WIN32, which covers even Win64 and CE, file
             * descriptors referenced by BIO_s_fd are not inherited
             * by child process and therefore below is not an option.
             * It could have been an option if bss_fd.c was operating
             * on real Windows descriptors, such as those obtained
             * with CreateFile.
             */
        } else if (strncmp(arg, "fd:", 3) == 0) {
            BIO *btmp;
            i = atoi(arg + 3);
            if (i >= 0)
                pwdbio = BIO_new_fd(i, BIO_NOCLOSE);
            if ((i < 0) || !pwdbio) {
                BIO_printf(bio_err, "Can't access file descriptor %s\n", arg + 3);
                return NULL;
            }
            /*
             * Can't do BIO_gets on an fd BIO so add a buffering BIO
             */
            btmp = BIO_new(BIO_f_buffer());
            pwdbio = BIO_push(btmp, pwdbio);
#endif
        } else if (strcmp(arg, "stdin") == 0) {
            pwdbio = dup_bio_in(FORMAT_TEXT);
            if (!pwdbio) {
                BIO_printf(bio_err, "Can't open BIO for stdin\n");
                return NULL;
            }
        } else {
            BIO_printf(bio_err, "Invalid password argument \"%s\"\n", arg);
            return NULL;
        }
    }
    i = BIO_gets(pwdbio, tpass, APP_PASS_LEN);
    if (keepbio != 1) {
        BIO_free_all(pwdbio);
        pwdbio = NULL;
    }
    if (i <= 0) {
        BIO_printf(bio_err, "Error reading password from BIO\n");
        return NULL;
    }
    tmp = strchr(tpass, '\n');
    if (tmp != NULL)
        *tmp = 0;
    return OPENSSL_strdup(tpass);
}