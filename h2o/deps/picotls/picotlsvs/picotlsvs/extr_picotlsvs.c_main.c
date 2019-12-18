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

/* Variables and functions */
 size_t nb_test_keys ; 
 int openPemTest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int ptls_memory_loopback_test (int,int,char*,char*) ; 
 int /*<<< orphan*/ * test_keys ; 

int main()
{
	int ret = 0;

#if 1
	/* TODO: move to ASN.1 unit test*/

	for (size_t i = 0; ret == 0 && i < nb_test_keys; i++)
	{
		ret = openPemTest(test_keys[i]);
	}
#endif

	if (ret == 0)
	{
		printf("\nStarting the RSA test with OpenSSL\n");
		ret = ptls_memory_loopback_test(1, 1, "key.pem", "cert.pem");
	}

	if (ret == 0)
	{
		printf("\nStarting the P256R1 test with OpenSSL\n");
		ret = ptls_memory_loopback_test(1, 1, "ec_key.pem", "ec_cert.pem");
	}

	if (ret == 0)
	{
		printf("\nStarting the P256R1 test with OpenSSL server and Minicrypto client\n");
		ret = ptls_memory_loopback_test(0, 1, "ec_key.pem", "ec_cert.pem");
	}

	if (ret == 0)
	{
		printf("\nStarting the P256R1 test with Minicrypto\n");
		ret = ptls_memory_loopback_test(0, 0, "ec_key.pem", "ec_cert.pem");
	}

	if (ret == 0)
	{
		printf("\nStarting the P256R1 test with Minicrypto server and OpenSSL client\n");
		ret = ptls_memory_loopback_test(1, 0, "ec_key.pem", "ec_cert.pem");
	}

    return ret;
}