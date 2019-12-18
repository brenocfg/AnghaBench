#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  SHA512; int /*<<< orphan*/  SHA256; int /*<<< orphan*/  SHA1; int /*<<< orphan*/  RIPEMD160; int /*<<< orphan*/  MD5; } ;
typedef  TYPE_1__ DIGEST_CTX ;

/* Variables and functions */
#define  DIGEST_MD5 132 
#define  DIGEST_RIPEMD160 131 
#define  DIGEST_SHA1 130 
#define  DIGEST_SHA256 129 
#define  DIGEST_SHA512 128 
 char* MD5End (int /*<<< orphan*/ *,char*) ; 
 char* RIPEMD160_End (int /*<<< orphan*/ *,char*) ; 
 char* SHA1_End (int /*<<< orphan*/ *,char*) ; 
 char* SHA256_End (int /*<<< orphan*/ *,char*) ; 
 char* SHA512_End (int /*<<< orphan*/ *,char*) ; 
 int digesttype ; 

__attribute__((used)) static char *
digest_end(DIGEST_CTX *c, char *buf)
{

	switch (digesttype) {
	case DIGEST_MD5:
		return (MD5End(&(c->MD5), buf));
	case DIGEST_RIPEMD160:
		return (RIPEMD160_End(&(c->RIPEMD160), buf));
	case DIGEST_SHA1:
		return (SHA1_End(&(c->SHA1), buf));
	case DIGEST_SHA256:
		return (SHA256_End(&(c->SHA256), buf));
	case DIGEST_SHA512:
		return (SHA512_End(&(c->SHA512), buf));
	default:
		return (NULL);
	}
}