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
struct ber_element {size_t be_len; int be_free; void* be_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TYPE_BITSTRING ; 
 int /*<<< orphan*/  bcopy (void const*,void*,size_t) ; 
 struct ber_element* ber_get_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_link_elements (struct ber_element*,struct ber_element*) ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 

struct ber_element *
ber_add_bitstring(struct ber_element *prev, const void *v0, size_t len)
{
	struct ber_element *elm;
	void *v;

	if ((v = calloc(1, len)) == NULL)
		return NULL;
	if ((elm = ber_get_element(BER_TYPE_BITSTRING)) == NULL) {
		free(v);
		return NULL;
	}

	bcopy(v0, v, len);
	elm->be_val = v;
	elm->be_len = len;
	elm->be_free = 1;		/* free string on cleanup */

	ber_link_elements(prev, elm);

	return elm;
}