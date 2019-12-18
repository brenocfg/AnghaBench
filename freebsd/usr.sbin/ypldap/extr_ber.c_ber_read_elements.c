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
struct ber {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct ber_element*) ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 struct ber_element* ber_get_element (int /*<<< orphan*/ ) ; 
 int ber_read_element (struct ber*,struct ber_element*) ; 

struct ber_element *
ber_read_elements(struct ber *ber, struct ber_element *elm)
{
	struct ber_element *root = elm;

	if (root == NULL) {
		if ((root = ber_get_element(0)) == NULL)
			return NULL;
	}

	DPRINTF("read ber elements, root %p\n", root);

	if (ber_read_element(ber, root) == -1) {
		/* Cleanup if root was allocated by us */
		if (elm == NULL)
			ber_free_elements(root);
		return NULL;
	}

	return root;
}