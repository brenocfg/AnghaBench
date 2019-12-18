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
struct skcipher_request {int dummy; } ;
struct cipher_test_sglists {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int test_skcipher_vs_generic_impl(const char *driver,
					 const char *generic_driver,
					 struct skcipher_request *req,
					 struct cipher_test_sglists *tsgls)
{
	return 0;
}