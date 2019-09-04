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
struct refspec_item {char* src; char* dst; } ;
struct refspec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct refspec_item*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ query_refspecs (struct refspec*,struct refspec_item*) ; 

char *apply_refspecs(struct refspec *rs, const char *name)
{
	struct refspec_item query;

	memset(&query, 0, sizeof(struct refspec_item));
	query.src = (char *)name;

	if (query_refspecs(rs, &query))
		return NULL;

	return query.dst;
}