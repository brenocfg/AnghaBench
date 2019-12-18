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
typedef  char u_char ;
struct nb_name {char* nn_scope; } ;

/* Variables and functions */
 int NB_ENCNAMELEN ; 
 int NB_MAXLABLEN ; 

int
nb_name_len(struct nb_name *np)
{
	u_char *name;
	int len, sclen;

	len = 1 + NB_ENCNAMELEN;
	if (np->nn_scope == NULL)
		return len + 1;
	sclen = 0;
	for (name = np->nn_scope; *name; name++) {
		if (*name == '.') {
			sclen = 0;
		} else {
			if (sclen < NB_MAXLABLEN) {
				sclen++;
				len++;
			}
		}
	}
	return len + 1;
}