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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct regional {int dummy; } ;
struct edns_option {size_t opt_len; struct edns_option* next; int /*<<< orphan*/ * opt_data; int /*<<< orphan*/  opt_code; } ;

/* Variables and functions */
 scalar_t__ regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/ * regional_alloc_init (struct regional*,int /*<<< orphan*/ *,size_t) ; 

int edns_opt_list_append(struct edns_option** list, uint16_t code, size_t len,
	uint8_t* data, struct regional* region)
{
	struct edns_option** prevp;
	struct edns_option* opt;

	/* allocate new element */
	opt = (struct edns_option*)regional_alloc(region, sizeof(*opt));
	if(!opt)
		return 0;
	opt->next = NULL;
	opt->opt_code = code;
	opt->opt_len = len;
	opt->opt_data = NULL;
	if(len > 0) {
		opt->opt_data = regional_alloc_init(region, data, len);
		if(!opt->opt_data)
			return 0;
	}

	/* append at end of list */
	prevp = list;
	while(*prevp != NULL) {
		prevp = &((*prevp)->next);
	}
	*prevp = opt;
	return 1;
}