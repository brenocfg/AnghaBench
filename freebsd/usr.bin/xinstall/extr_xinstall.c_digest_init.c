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
#define  DIGEST_MD5 133 
#define  DIGEST_NONE 132 
#define  DIGEST_RIPEMD160 131 
#define  DIGEST_SHA1 130 
#define  DIGEST_SHA256 129 
#define  DIGEST_SHA512 128 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RIPEMD160_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Init (int /*<<< orphan*/ *) ; 
 int digesttype ; 

__attribute__((used)) static void
digest_init(DIGEST_CTX *c)
{

	switch (digesttype) {
	case DIGEST_NONE:
		break;
	case DIGEST_MD5:
		MD5Init(&(c->MD5));
		break;
	case DIGEST_RIPEMD160:
		RIPEMD160_Init(&(c->RIPEMD160));
		break;
	case DIGEST_SHA1:
		SHA1_Init(&(c->SHA1));
		break;
	case DIGEST_SHA256:
		SHA256_Init(&(c->SHA256));
		break;
	case DIGEST_SHA512:
		SHA512_Init(&(c->SHA512));
		break;
	}
}