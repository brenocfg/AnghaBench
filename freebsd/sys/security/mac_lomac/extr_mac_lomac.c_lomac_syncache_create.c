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
struct mac_lomac {int dummy; } ;
struct label {int dummy; } ;
struct inpcb {struct label* inp_label; } ;

/* Variables and functions */
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  lomac_copy (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static void
lomac_syncache_create(struct label *label, struct inpcb *inp)
{
	struct mac_lomac *source, *dest;

	source = SLOT(inp->inp_label);
	dest = SLOT(label);
	lomac_copy(source, dest);
}