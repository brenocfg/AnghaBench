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
struct ber_element {scalar_t__ be_type; struct ber_element* be_next; } ;

/* Variables and functions */
 scalar_t__ BER_TYPE_OCTETSTRING ; 
 int /*<<< orphan*/  ber_get_string (struct ber_element*,char**) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  free (char**) ; 
 char* utoa (char*) ; 

char **
aldap_get_stringset(struct ber_element *elm)
{
	struct ber_element *a;
	int i;
	char **ret;
	char *s;

	if (elm->be_type != BER_TYPE_OCTETSTRING)
		return NULL;

	for (a = elm, i = 1; i > 0 && a != NULL && a->be_type ==
	    BER_TYPE_OCTETSTRING; a = a->be_next, i++)
		;
	if (i == 1)
		return NULL;

	if ((ret = calloc(i + 1, sizeof(char *))) == NULL)
		return NULL;

	for (a = elm, i = 0; a != NULL && a->be_type == BER_TYPE_OCTETSTRING;
	    a = a->be_next) {

		ber_get_string(a, &s);
		ret[i] = utoa(s);
		if (ret[i] != NULL)
			i++;
		
	}
	if (i == 0) {
		free(ret);
		return NULL;
	}
	ret[i] = NULL;

	return ret;
}