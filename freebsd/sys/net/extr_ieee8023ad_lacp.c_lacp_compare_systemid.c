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
struct lacp_systemid {int dummy; } ;

/* Variables and functions */
 int memcmp (struct lacp_systemid const*,struct lacp_systemid const*,int) ; 

__attribute__((used)) static int
lacp_compare_systemid(const struct lacp_systemid *a,
    const struct lacp_systemid *b)
{
	return (memcmp(a, b, sizeof(*a)));
}