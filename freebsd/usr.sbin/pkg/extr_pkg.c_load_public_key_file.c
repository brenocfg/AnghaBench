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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/ * PEM_read_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static EVP_PKEY *
load_public_key_file(const char *file)
{
	EVP_PKEY *pkey;
	BIO *bp;
	char errbuf[1024];

	bp = BIO_new_file(file, "r");
	if (!bp)
		errx(EXIT_FAILURE, "Unable to read %s", file);

	if ((pkey = PEM_read_bio_PUBKEY(bp, NULL, NULL, NULL)) == NULL)
		warnx("ici: %s", ERR_error_string(ERR_get_error(), errbuf));

	BIO_free(bp);

	return (pkey);
}