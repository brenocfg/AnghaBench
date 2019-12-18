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
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  EVP_sha224 () ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  EVP_sha384 () ; 
 int /*<<< orphan*/  EVP_sha512 () ; 
 int /*<<< orphan*/  MAX_LENGTH ; 
 int /*<<< orphan*/  emit_length_test (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
  emit_length_test("SHA1", EVP_sha1(), MAX_LENGTH);
  emit_length_test("SHA224", EVP_sha224(), MAX_LENGTH);
  emit_length_test("SHA256", EVP_sha256(), MAX_LENGTH);
  emit_length_test("SHA384", EVP_sha384(), MAX_LENGTH);
  emit_length_test("SHA512", EVP_sha512(), MAX_LENGTH);
  return 0;
}