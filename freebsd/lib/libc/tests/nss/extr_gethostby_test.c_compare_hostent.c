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
struct hostent {char* h_name; scalar_t__ h_addrtype; char** h_aliases; char** h_addr_list; int /*<<< orphan*/  h_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_hostent (struct hostent*) ; 
 scalar_t__ memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static  int
compare_hostent(struct hostent *ht1, struct hostent *ht2, void *mdata)
{
	char **c1, **c2, **ct, **cb;
	int b;

	if (ht1 == ht2)
		return 0;

	if (ht1 == NULL || ht2 == NULL)
		goto errfin;

	if (ht1->h_name == NULL || ht2->h_name == NULL)
		goto errfin;

	if (ht1->h_addrtype != ht2->h_addrtype ||
	    ht1->h_length != ht2->h_length ||
	    strcmp(ht1->h_name, ht2->h_name) != 0)
		goto errfin;

	c1 = ht1->h_aliases;
	c2 = ht2->h_aliases;

	if ((ht1->h_aliases == NULL || ht2->h_aliases == NULL) &&
	    ht1->h_aliases != ht2->h_aliases)
		goto errfin;

	if (c1 != NULL && c2 != NULL) {
		cb = c1;
		for (;*c1; ++c1) {
			b = 0;
			for (ct = c2; *ct; ++ct) {
				if (strcmp(*c1, *ct) == 0) {
					b = 1;
					break;
				}
			}
			if (b == 0) {
				printf("h1 aliases item can't be found in h2 "
				    "aliases\n");
				goto errfin;
			}
		}

		c1 = cb;
		for (;*c2; ++c2) {
			b = 0;
			for (ct = c1; *ct; ++ct) {
				if (strcmp(*c2, *ct) == 0) {
					b = 1;
					break;
				}
			}
			if (b == 0) {
				printf("h2 aliases item can't be found in h1 "
				    "aliases\n");
				goto errfin;
			}
		}
	}

	c1 = ht1->h_addr_list;
	c2 = ht2->h_addr_list;

	if ((ht1->h_addr_list == NULL || ht2->h_addr_list== NULL) &&
	    ht1->h_addr_list != ht2->h_addr_list)
		goto errfin;

	if (c1 != NULL && c2 != NULL) {
		cb = c1;
		for (; *c1; ++c1) {
			b = 0;
			for (ct = c2; *ct; ++ct) {
				if (memcmp(*c1, *ct, ht1->h_length) == 0) {
					b = 1;
					break;
				}
			}
			if (b == 0) {
				printf("h1 addresses item can't be found in "
				    "h2 addresses\n");
				goto errfin;
			}
		}

		c1 = cb;
		for (; *c2; ++c2) {
			b = 0;
			for (ct = c1; *ct; ++ct) {
				if (memcmp(*c2, *ct, ht1->h_length) == 0) {
					b = 1;
					break;
				}
			}
			if (b == 0) {
				printf("h2 addresses item can't be found in "
				    "h1 addresses\n");
				goto errfin;
			}
		}
	}

	return 0;

errfin:
	if (mdata == NULL) {
		printf("following structures are not equal:\n");
		dump_hostent(ht1);
		dump_hostent(ht2);
	}

	return (-1);
}