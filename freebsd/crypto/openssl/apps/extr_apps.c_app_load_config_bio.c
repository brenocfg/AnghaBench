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
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 int NCONF_load_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/ * NCONF_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  opt_getprog () ; 

CONF *app_load_config_bio(BIO *in, const char *filename)
{
    long errorline = -1;
    CONF *conf;
    int i;

    conf = NCONF_new(NULL);
    i = NCONF_load_bio(conf, in, &errorline);
    if (i > 0)
        return conf;

    if (errorline <= 0) {
        BIO_printf(bio_err, "%s: Can't load ", opt_getprog());
    } else {
        BIO_printf(bio_err, "%s: Error on line %ld of ", opt_getprog(),
                   errorline);
    }
    if (filename != NULL)
        BIO_printf(bio_err, "config file \"%s\"\n", filename);
    else
        BIO_printf(bio_err, "config input");

    NCONF_free(conf);
    return NULL;
}