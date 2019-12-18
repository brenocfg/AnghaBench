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
typedef  int /*<<< orphan*/  u_int32_t ;
struct compression_types {int /*<<< orphan*/  comp_number; scalar_t__ name; } ;

/* Variables and functions */
 struct compression_types* comp_types ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static u_int32_t
stringtocomp(const char *s)
{
	const struct compression_types *ct;
	size_t l = strlen(s);

	for (ct = comp_types; ct->name; ct++)
		if (strncasecmp(ct->name, s, l) == 0)
			break;

	return(ct->comp_number);
}