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
struct nb_name {char* nn_name; char nn_type; char* nn_scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  NB_ENCNAMELEN ; 
 int NB_MAXLABLEN ; 
 int NB_NAMELEN ; 
 int /*<<< orphan*/  nb_char_encode (char**,char,int) ; 
 int nb_encname_len (char*) ; 
 char toupper (int /*<<< orphan*/ ) ; 

int
nb_name_encode(struct nb_name *np, u_char *dst)
{
	u_char *name, *plen;
	u_char *cp = dst;
	int i, lblen;

	*cp++ = NB_ENCNAMELEN;
	name = np->nn_name;
	if (name[0] == '*' && name[1] == 0) {
		nb_char_encode(&cp, '*', 1);
		nb_char_encode(&cp, ' ', NB_NAMELEN - 1);
	} else {
		for (i = 0; i < NB_NAMELEN - 1; i++)
			if (*name != 0)
				nb_char_encode(&cp, toupper(*name++), 1);
			else
				nb_char_encode(&cp, ' ', 1);
		nb_char_encode(&cp, np->nn_type, 1);
	}
	*cp = 0;
	if (np->nn_scope == NULL)
		return nb_encname_len(dst);
	plen = cp++;
	lblen = 0;
	for (name = np->nn_scope; ; name++) {
		if (*name == '.' || *name == 0) {
			*plen = lblen;
			plen = cp++;
			*plen = 0;
			if (*name == 0)
				break;
		} else {
			if (lblen < NB_MAXLABLEN) {
				*cp++ = *name;
				lblen++;
			}
		}
	}
	return nb_encname_len(dst);
}