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
 int nonce_function_rfc6979 (unsigned char*,unsigned char const*,unsigned char const*,unsigned char const*,void*,unsigned int) ; 

__attribute__((used)) static int nonce_function_test_fail(unsigned char *nonce32, const unsigned char *msg32, const unsigned char *key32, const unsigned char *algo16, void *data, unsigned int counter) {
   /* Dummy nonce generator that has a fatal error on the first counter value. */
   if (counter == 0) {
       return 0;
   }
   return nonce_function_rfc6979(nonce32, msg32, key32, algo16, data, counter - 1);
}