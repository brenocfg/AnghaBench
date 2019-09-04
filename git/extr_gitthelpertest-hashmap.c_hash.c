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
#define  HASH_METHOD_0 131 
#define  HASH_METHOD_FNV 130 
#define  HASH_METHOD_I 129 
#define  HASH_METHOD_IDIV10 128 
 unsigned int HASH_METHOD_X2 ; 
 unsigned int strhash (char const*) ; 

__attribute__((used)) static unsigned int hash(unsigned int method, unsigned int i, const char *key)
{
	unsigned int hash = 0;
	switch (method & 3)
	{
	case HASH_METHOD_FNV:
		hash = strhash(key);
		break;
	case HASH_METHOD_I:
		hash = i;
		break;
	case HASH_METHOD_IDIV10:
		hash = i / 10;
		break;
	case HASH_METHOD_0:
		hash = 0;
		break;
	}

	if (method & HASH_METHOD_X2)
		hash = 2 * hash;
	return hash;
}