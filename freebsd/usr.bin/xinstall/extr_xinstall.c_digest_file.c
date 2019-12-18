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
#define  DIGEST_MD5 132 
#define  DIGEST_RIPEMD160 131 
#define  DIGEST_SHA1 130 
#define  DIGEST_SHA256 129 
#define  DIGEST_SHA512 128 
 char* MD5File (char const*,int /*<<< orphan*/ *) ; 
 char* RIPEMD160_File (char const*,int /*<<< orphan*/ *) ; 
 char* SHA1_File (char const*,int /*<<< orphan*/ *) ; 
 char* SHA256_File (char const*,int /*<<< orphan*/ *) ; 
 char* SHA512_File (char const*,int /*<<< orphan*/ *) ; 
 int digesttype ; 

__attribute__((used)) static char *
digest_file(const char *name)
{

	switch (digesttype) {
	case DIGEST_MD5:
		return (MD5File(name, NULL));
	case DIGEST_RIPEMD160:
		return (RIPEMD160_File(name, NULL));
	case DIGEST_SHA1:
		return (SHA1_File(name, NULL));
	case DIGEST_SHA256:
		return (SHA256_File(name, NULL));
	case DIGEST_SHA512:
		return (SHA512_File(name, NULL));
	default:
		return (NULL);
	}
}