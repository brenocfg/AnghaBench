#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ber_element {TYPE_1__* be_next; struct ber_element* be_sub; } ;
struct ber {int fd; int /*<<< orphan*/ * br_wbuf; } ;
struct aldap_page_control {char* size; int cookie_len; int /*<<< orphan*/ * cookie; } ;
struct TYPE_2__ {int be_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ber_free (struct ber*) ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 struct ber_element* ber_read_elements (struct ber*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ber_scanf_elements (struct ber_element*,char*,char**,char**) ; 
 int /*<<< orphan*/  ber_set_readbuf (struct ber*,char*,int) ; 
 int /*<<< orphan*/  free (struct aldap_page_control*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

struct aldap_page_control *
aldap_parse_page_control(struct ber_element *control, size_t len) 
{
	char *oid, *s;
	char *encoded;
	struct ber b;
	struct ber_element *elm;
	struct aldap_page_control *page;

	b.br_wbuf = NULL;
	b.fd = -1;
	ber_scanf_elements(control, "ss", &oid, &encoded);
	ber_set_readbuf(&b, encoded, control->be_next->be_len);
	elm = ber_read_elements(&b, NULL);

	if ((page = malloc(sizeof(struct aldap_page_control))) == NULL) {
		if (elm != NULL)
			ber_free_elements(elm);
		ber_free(&b);
		return NULL;
	}

	ber_scanf_elements(elm->be_sub, "is", &page->size, &s);
	page->cookie_len = elm->be_sub->be_next->be_len;

	if ((page->cookie = malloc(page->cookie_len)) == NULL) {
		if (elm != NULL)
			ber_free_elements(elm);
		ber_free(&b);
		free(page);
		return NULL;
	}
	memcpy(page->cookie, s, page->cookie_len);

	ber_free_elements(elm);
	ber_free(&b);
	return page;
}