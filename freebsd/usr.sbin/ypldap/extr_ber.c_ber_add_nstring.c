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
struct ber_element {char* be_val; size_t be_len; int be_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TYPE_OCTETSTRING ; 
 int /*<<< orphan*/  bcopy (char const*,char*,size_t) ; 
 struct ber_element* ber_get_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_link_elements (struct ber_element*,struct ber_element*) ; 
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 

struct ber_element *
ber_add_nstring(struct ber_element *prev, const char *string0, size_t len)
{
	struct ber_element *elm;
	char *string;

	if ((string = calloc(1, len)) == NULL)
		return NULL;
	if ((elm = ber_get_element(BER_TYPE_OCTETSTRING)) == NULL) {
		free(string);
		return NULL;
	}

	bcopy(string0, string, len);
	elm->be_val = string;
	elm->be_len = len;
	elm->be_free = 1;		/* free string on cleanup */

	ber_link_elements(prev, elm);

	return elm;
}