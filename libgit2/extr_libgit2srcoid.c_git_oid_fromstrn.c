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
 size_t GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_OID_RAWSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int git__fromhex (char const) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oid_error_invalid (char*) ; 

int git_oid_fromstrn(git_oid *out, const char *str, size_t length)
{
	size_t p;
	int v;

	assert(out && str);

	if (!length)
		return oid_error_invalid("too short");

	if (length > GIT_OID_HEXSZ)
		return oid_error_invalid("too long");

	memset(out->id, 0, GIT_OID_RAWSZ);

	for (p = 0; p < length; p++) {
		v = git__fromhex(str[p]);
		if (v < 0)
			return oid_error_invalid("contains invalid characters");

		out->id[p / 2] |= (unsigned char)(v << (p % 2 ? 0 : 4));
	}

	return 0;
}