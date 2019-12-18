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
typedef  int /*<<< orphan*/  RSA_METHOD ;
typedef  int /*<<< orphan*/  DH_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/ * DH_get_default_method () ; 
 char* DH_meth_get0_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENGINE_add_conf_module () ; 
 int RAND_status () ; 
 int /*<<< orphan*/ * RSA_get_default_method () ; 
 char* RSA_meth_get0_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
info(void *opt, int argc, char **argv)
{

    ENGINE_add_conf_module();

    {
	const RSA_METHOD *m = RSA_get_default_method();
	if (m != NULL)
	    printf("rsa: %s\n", RSA_meth_get0_name(m));
    }
    {
	const DH_METHOD *m = DH_get_default_method();
	if (m != NULL)
	    printf("dh: %s\n", DH_meth_get0_name(m));
    }
#ifdef HAVE_OPENSSL
    {
	printf("ecdsa: ECDSA_METHOD-not-export\n");
    }
#else
    {
	printf("ecdsa: hcrypto null\n");
    }
#endif
    {
	int ret = RAND_status();
	printf("rand: %s\n", ret == 1 ? "ok" : "not available");
    }

    return 0;
}