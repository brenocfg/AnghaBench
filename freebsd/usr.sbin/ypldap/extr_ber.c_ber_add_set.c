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
struct ber_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TYPE_SET ; 
 struct ber_element* ber_get_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_link_elements (struct ber_element*,struct ber_element*) ; 

struct ber_element *
ber_add_set(struct ber_element *prev)
{
	struct ber_element *elm;

	if ((elm = ber_get_element(BER_TYPE_SET)) == NULL)
		return NULL;

	ber_link_elements(prev, elm);

	return elm;
}