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
struct TYPE_3__ {unsigned char* id; } ;
typedef  TYPE_1__ git_oid ;

/* Variables and functions */
 int GIT_OID_RAWSZ ; 
 int git__fromhex (int /*<<< orphan*/ ) ; 

int git_oid_strcmp(const git_oid *oid_a, const char *str)
{
	const unsigned char *a;
	unsigned char strval;
	int hexval;

	for (a = oid_a->id; *str && (a - oid_a->id) < GIT_OID_RAWSZ; ++a) {
		if ((hexval = git__fromhex(*str++)) < 0)
			return -1;
		strval = (unsigned char)(hexval << 4);
		if (*str) {
			if ((hexval = git__fromhex(*str++)) < 0)
				return -1;
			strval |= hexval;
		}
		if (*a != strval)
			return (*a - strval);
	}

	return 0;
}