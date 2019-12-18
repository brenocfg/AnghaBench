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
struct mc_request {int dummy; } ;

/* Variables and functions */
 int mconsole_reply_len (struct mc_request*,char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int mconsole_reply(struct mc_request *req, const char *str, int err, int more)
{
	return mconsole_reply_len(req, str, strlen(str), err, more);
}