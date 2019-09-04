#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* hash; } ;
struct disambiguate_state {unsigned char* hex_pfx; int len; TYPE_1__ bin_pfx; } ;
struct TYPE_4__ {int hexsz; } ;

/* Variables and functions */
 int MINIMUM_ABBREV ; 
 int /*<<< orphan*/  memset (struct disambiguate_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prepare_alt_odb (int /*<<< orphan*/ ) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int init_object_disambiguation(const char *name, int len,
				      struct disambiguate_state *ds)
{
	int i;

	if (len < MINIMUM_ABBREV || len > the_hash_algo->hexsz)
		return -1;

	memset(ds, 0, sizeof(*ds));

	for (i = 0; i < len ;i++) {
		unsigned char c = name[i];
		unsigned char val;
		if (c >= '0' && c <= '9')
			val = c - '0';
		else if (c >= 'a' && c <= 'f')
			val = c - 'a' + 10;
		else if (c >= 'A' && c <='F') {
			val = c - 'A' + 10;
			c -= 'A' - 'a';
		}
		else
			return -1;
		ds->hex_pfx[i] = c;
		if (!(i & 1))
			val <<= 4;
		ds->bin_pfx.hash[i >> 1] |= val;
	}

	ds->len = len;
	ds->hex_pfx[len] = '\0';
	prepare_alt_odb(the_repository);
	return 0;
}