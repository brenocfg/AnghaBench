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
struct poly1305_kat {int /*<<< orphan*/  vector_name; } ;
typedef  int /*<<< orphan*/  hbyte ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (size_t,size_t,char*,...) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,char*) ; 
 size_t strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 

__attribute__((used)) static void
parse_hex(const struct poly1305_kat *kat, const char *hexstr, void *voutput,
    size_t explen)
{
	/* Space or colon delimited; may contain a single trailing space;
	 * length should match exactly.
	 */
	const char *sep, *it;
	size_t sym_len, count;
	char hbyte[3], *out;
	int res;

	out = voutput;
	memset(hbyte, 0, sizeof(hbyte));

	it = hexstr;
	count = 0;
	while (true) {
		sep = strpbrk(it, " :");
		if (sep == NULL)
			sym_len = strlen(it);
		else
			sym_len = sep - it;

		ATF_REQUIRE_EQ_MSG(sym_len, 2,
		    "invalid hex byte '%.*s' in vector %s", (int)sym_len, it,
		    kat->vector_name);

		memcpy(hbyte, it, 2);
		res = sscanf(hbyte, "%hhx", &out[count]);
		ATF_REQUIRE_EQ_MSG(res, 1,
		    "invalid hex byte '%s' in vector %s", hbyte,
		    kat->vector_name);

		count++;
		ATF_REQUIRE_MSG(count <= explen,
		    "got longer than expected value at %s", kat->vector_name);

		if (sep == NULL)
			break;
		it = sep;
		while (*it == ' ' || *it == ':')
			it++;
		if (*it == 0)
			break;
	}

	ATF_REQUIRE_EQ_MSG(count, explen, "got short value at %s",
	    kat->vector_name);
}