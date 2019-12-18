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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ber_oid {int dummy; } ;
struct ber_element {size_t be_len; int be_free; int /*<<< orphan*/ * be_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TYPE_OBJECT ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 struct ber_element* ber_get_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_link_elements (struct ber_element*,struct ber_element*) ; 
 size_t ber_oid2ber (struct ber_oid*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * calloc (int,size_t) ; 

struct ber_element *
ber_add_oid(struct ber_element *prev, struct ber_oid *o)
{
	struct ber_element	*elm;
	u_int8_t		*buf;
	size_t			 len;

	if ((elm = ber_get_element(BER_TYPE_OBJECT)) == NULL)
		return (NULL);

	if ((len = ber_oid2ber(o, NULL, 0)) == 0)
		goto fail;

	if ((buf = calloc(1, len)) == NULL)
		goto fail;

	elm->be_val = buf;
	elm->be_len = len;
	elm->be_free = 1;

	if (ber_oid2ber(o, buf, len) != len)
		goto fail;

	ber_link_elements(prev, elm);

	return (elm);

 fail:
	ber_free_elements(elm);
	return (NULL);
}