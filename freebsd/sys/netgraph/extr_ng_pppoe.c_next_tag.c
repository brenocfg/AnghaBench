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
struct pppoe_tag {int dummy; } ;
struct pppoe_hdr {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline const struct pppoe_tag*
next_tag(const struct pppoe_hdr* ph)
{
	return (const struct pppoe_tag*)(((const char*)(ph + 1))
	    + ntohs(ph->length));
}