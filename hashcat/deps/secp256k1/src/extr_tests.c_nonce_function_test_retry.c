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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int nonce_function_rfc6979 (unsigned char*,unsigned char const*,unsigned char const*,unsigned char const*,void*,unsigned int) ; 

__attribute__((used)) static int nonce_function_test_retry(unsigned char *nonce32, const unsigned char *msg32, const unsigned char *key32, const unsigned char *algo16, void *data, unsigned int counter) {
   /* Dummy nonce generator that produces unacceptable nonces for the first several counter values. */
   if (counter < 3) {
       memset(nonce32, counter==0 ? 0 : 255, 32);
       if (counter == 2) {
           nonce32[31]--;
       }
       return 1;
   }
   if (counter < 5) {
       static const unsigned char order[] = {
           0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
           0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
           0xBA,0xAE,0xDC,0xE6,0xAF,0x48,0xA0,0x3B,
           0xBF,0xD2,0x5E,0x8C,0xD0,0x36,0x41,0x41
       };
       memcpy(nonce32, order, 32);
       if (counter == 4) {
           nonce32[31]++;
       }
       return 1;
   }
   /* Retry rate of 6979 is negligible esp. as we only call this in deterministic tests. */
   /* If someone does fine a case where it retries for secp256k1, we'd like to know. */
   if (counter > 5) {
       return 0;
   }
   return nonce_function_rfc6979(nonce32, msg32, key32, algo16, data, counter - 5);
}