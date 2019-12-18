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
 int EIO ; 
 int /*<<< orphan*/ ** features_for_read ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  roundup (int,int) ; 
 int /*<<< orphan*/  xdr_int (unsigned char const**,int*) ; 

__attribute__((used)) static int
nvlist_check_features_for_read(const unsigned char *nvlist)
{
	const unsigned char *p, *pair;
	int junk;
	int encoded_size, decoded_size;
	int rc;

	rc = 0;

	p = nvlist;
	xdr_int(&p, &junk);
	xdr_int(&p, &junk);

	pair = p;
	xdr_int(&p, &encoded_size);
	xdr_int(&p, &decoded_size);
	while (encoded_size && decoded_size) {
		int namelen, pairtype;
		const char *pairname;
		int i, found;

		found = 0;

		xdr_int(&p, &namelen);
		pairname = (const char*) p;
		p += roundup(namelen, 4);
		xdr_int(&p, &pairtype);

		for (i = 0; features_for_read[i] != NULL; i++) {
			if (!memcmp(pairname, features_for_read[i], namelen)) {
				found = 1;
				break;
			}
		}

		if (!found) {
			printf("ZFS: unsupported feature: %s\n", pairname);
			rc = EIO;
		}

		p = pair + encoded_size;

		pair = p;
		xdr_int(&p, &encoded_size);
		xdr_int(&p, &decoded_size);
	}

	return (rc);
}