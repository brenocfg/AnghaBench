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
struct ip {int dummy; } ;
struct alias_data {int /*<<< orphan*/  maxpktsize; int /*<<< orphan*/  lnk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AliasHandleIrcOut (struct libalias*,struct ip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKTSIZE ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ newpacket ; 

__attribute__((used)) static int
protohandler(struct libalias *la, struct ip *pip, struct alias_data *ah)
{

	newpacket = malloc(PKTSIZE);
	if (newpacket) {
		AliasHandleIrcOut(la, pip, ah->lnk, ah->maxpktsize);
		free(newpacket);
	}
	return (0);
}