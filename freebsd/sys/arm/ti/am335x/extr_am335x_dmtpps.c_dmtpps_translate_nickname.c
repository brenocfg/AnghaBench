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
struct nicknames {char const* name; int /*<<< orphan*/ * nick; } ;

/* Variables and functions */
 struct nicknames* dmtpps_pin_nicks ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
dmtpps_translate_nickname(const char *nick)
{
	struct nicknames *nn;

	for (nn = dmtpps_pin_nicks; nn->nick != NULL; nn++)
		if (strcasecmp(nick, nn->nick) == 0)
			return nn->name;
	return (nick);
}