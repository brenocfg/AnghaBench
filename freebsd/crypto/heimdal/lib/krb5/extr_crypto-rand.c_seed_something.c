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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  seedfile ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENTROPY_NEEDED ; 
 int O_BINARY ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RAND_add (char*,scalar_t__,double) ; 
 int /*<<< orphan*/  RAND_egd_bytes (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ RAND_file_name (char*,int) ; 
 int RAND_status () ; 
 int /*<<< orphan*/  RAND_write_file (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 char* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_init_context (int /*<<< orphan*/ *) ; 
 int open (char*,int) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  rk_cloexec (int) ; 

__attribute__((used)) static int
seed_something(void)
{
    char buf[1024], seedfile[256];

    /* If there is a seed file, load it. But such a file cannot be trusted,
       so use 0 for the entropy estimate */
    if (RAND_file_name(seedfile, sizeof(seedfile))) {
	int fd;
	fd = open(seedfile, O_RDONLY | O_BINARY | O_CLOEXEC);
	if (fd >= 0) {
	    ssize_t ret;
	    rk_cloexec(fd);
	    ret = read(fd, buf, sizeof(buf));
	    if (ret > 0)
		RAND_add(buf, ret, 0.0);
	    close(fd);
	} else
	    seedfile[0] = '\0';
    } else
	seedfile[0] = '\0';

    /* Calling RAND_status() will try to use /dev/urandom if it exists so
       we do not have to deal with it. */
    if (RAND_status() != 1) {
#ifndef _WIN32
#ifndef OPENSSL_NO_EGD
	krb5_context context;
	const char *p;

	/* Try using egd */
	if (!krb5_init_context(&context)) {
	    p = krb5_config_get_string(context, NULL, "libdefaults",
				       "egd_socket", NULL);
	    if (p != NULL)
		RAND_egd_bytes(p, ENTROPY_NEEDED);
	    krb5_free_context(context);
	}
#endif
#else
	/* TODO: Once a Windows CryptoAPI RAND method is defined, we
	   can use that and failover to another method. */
#endif
    }

    if (RAND_status() == 1)	{
	/* Update the seed file */
	if (seedfile[0])
	    RAND_write_file(seedfile);

	return 0;
    } else
	return -1;
}