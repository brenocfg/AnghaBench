#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ unique_subject; } ;
struct TYPE_5__ {TYPE_1__ attributes; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ CA_DB ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int BIO_snprintf (char*,int,char*,char const*,...) ; 
 int BSIZE ; 
 int TXT_DB_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int strlen (char const*) ; 

int save_index(const char *dbfile, const char *suffix, CA_DB *db)
{
    char buf[3][BSIZE];
    BIO *out;
    int j;

    j = strlen(dbfile) + strlen(suffix);
    if (j + 6 >= BSIZE) {
        BIO_printf(bio_err, "file name too long\n");
        goto err;
    }
#ifndef OPENSSL_SYS_VMS
    j = BIO_snprintf(buf[2], sizeof(buf[2]), "%s.attr", dbfile);
    j = BIO_snprintf(buf[1], sizeof(buf[1]), "%s.attr.%s", dbfile, suffix);
    j = BIO_snprintf(buf[0], sizeof(buf[0]), "%s.%s", dbfile, suffix);
#else
    j = BIO_snprintf(buf[2], sizeof(buf[2]), "%s-attr", dbfile);
    j = BIO_snprintf(buf[1], sizeof(buf[1]), "%s-attr-%s", dbfile, suffix);
    j = BIO_snprintf(buf[0], sizeof(buf[0]), "%s-%s", dbfile, suffix);
#endif
    out = BIO_new_file(buf[0], "w");
    if (out == NULL) {
        perror(dbfile);
        BIO_printf(bio_err, "unable to open '%s'\n", dbfile);
        goto err;
    }
    j = TXT_DB_write(out, db->db);
    BIO_free(out);
    if (j <= 0)
        goto err;

    out = BIO_new_file(buf[1], "w");
    if (out == NULL) {
        perror(buf[2]);
        BIO_printf(bio_err, "unable to open '%s'\n", buf[2]);
        goto err;
    }
    BIO_printf(out, "unique_subject = %s\n",
               db->attributes.unique_subject ? "yes" : "no");
    BIO_free(out);

    return 1;
 err:
    return 0;
}