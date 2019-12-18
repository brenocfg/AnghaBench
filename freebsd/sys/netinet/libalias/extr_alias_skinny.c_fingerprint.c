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
struct libalias {scalar_t__ skinnyPort; } ;
struct alias_data {int /*<<< orphan*/ * dport; int /*<<< orphan*/ * sport; int /*<<< orphan*/ * lnk; } ;

/* Variables and functions */
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fingerprint(struct libalias *la, struct alias_data *ah)
{

	if (ah->dport == NULL || ah->sport == NULL || ah->lnk == NULL)
		return (-1);
	if (la->skinnyPort != 0 && (ntohs(*ah->sport) == la->skinnyPort ||
				    ntohs(*ah->dport) == la->skinnyPort))
		return (0);
	return (-1);
}