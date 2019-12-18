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
struct edns_option {scalar_t__ opt_code; scalar_t__ opt_len; int /*<<< orphan*/  opt_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int edns_opt_compare(struct edns_option* p, struct edns_option* q)
{
	if(!p && !q) return 0;
	if(!p) return -1;
	if(!q) return 1;
	log_assert(p && q);
	if(p->opt_code != q->opt_code)
		return (int)q->opt_code - (int)p->opt_code;
	if(p->opt_len != q->opt_len)
		return (int)q->opt_len - (int)p->opt_len;
	if(p->opt_len != 0)
		return memcmp(p->opt_data, q->opt_data, p->opt_len);
	return 0;
}