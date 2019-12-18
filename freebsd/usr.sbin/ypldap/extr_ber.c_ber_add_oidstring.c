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
struct ber_oid {int dummy; } ;
struct ber_element {int dummy; } ;

/* Variables and functions */
 struct ber_element* ber_add_oid (struct ber_element*,struct ber_oid*) ; 
 int ber_string2oid (char const*,struct ber_oid*) ; 

struct ber_element *
ber_add_oidstring(struct ber_element *prev, const char *oidstr)
{
	struct ber_oid		 o;

	if (ber_string2oid(oidstr, &o) == -1)
		return (NULL);

	return (ber_add_oid(prev, &o));
}