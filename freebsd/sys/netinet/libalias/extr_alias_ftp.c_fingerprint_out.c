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
struct libalias {int dummy; } ;
struct alias_data {scalar_t__ maxpktsize; int /*<<< orphan*/ * sport; int /*<<< orphan*/ * dport; int /*<<< orphan*/ * lnk; } ;

/* Variables and functions */
 scalar_t__ FTP_CONTROL_PORT_NUMBER ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fingerprint_out(struct libalias *la, struct alias_data *ah)
{

	if (ah->dport == NULL || ah->sport == NULL || ah->lnk == NULL ||
	    ah->maxpktsize == 0)
		return (-1);
	if (ntohs(*ah->dport) == FTP_CONTROL_PORT_NUMBER ||
	    ntohs(*ah->sport) == FTP_CONTROL_PORT_NUMBER)
		return (0);
	return (-1);
}