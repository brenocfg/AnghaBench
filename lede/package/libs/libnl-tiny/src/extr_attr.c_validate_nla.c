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
struct nlattr {int dummy; } ;
struct nla_policy {size_t type; int minlen; int maxlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t NLA_FLAG ; 
 size_t NLA_STRING ; 
 size_t NLA_TYPE_MAX ; 
 size_t NLA_UNSPEC ; 
 int NLE_INVAL ; 
 int NLE_RANGE ; 
 int* nla_attr_minlen ; 
 char* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_type (struct nlattr*) ; 

__attribute__((used)) static int validate_nla(struct nlattr *nla, int maxtype,
			struct nla_policy *policy)
{
	struct nla_policy *pt;
	int minlen = 0, type = nla_type(nla);

	if (type <= 0 || type > maxtype)
		return 0;

	pt = &policy[type];

	if (pt->type > NLA_TYPE_MAX)
		BUG();

	if (pt->minlen)
		minlen = pt->minlen;
	else if (pt->type != NLA_UNSPEC)
		minlen = nla_attr_minlen[pt->type];

	if (pt->type == NLA_FLAG && nla_len(nla) > 0)
		return -NLE_RANGE;

	if (nla_len(nla) < minlen)
		return -NLE_RANGE;

	if (pt->maxlen && nla_len(nla) > pt->maxlen)
		return -NLE_RANGE;

	if (pt->type == NLA_STRING) {
		char *data = nla_data(nla);
		if (data[nla_len(nla) - 1] != '\0')
			return -NLE_INVAL;
	}

	return 0;
}