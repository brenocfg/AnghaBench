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
typedef  int /*<<< orphan*/  uid_t ;
typedef  long time_t ;
struct user {int /*<<< orphan*/  spc30; int /*<<< orphan*/  spc60; int /*<<< orphan*/  spc90; int /*<<< orphan*/  space; int /*<<< orphan*/  count; } ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  time (long*) ; 
 struct user* user (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uses(uid_t uid, daddr_t blks, time_t act)
{
	static time_t today;
	struct user *usr;

	if (!today)
		time(&today);

	usr = user(uid);
	usr->count++;
	usr->space += blks;

	if (today - act > 90L * 24L * 60L * 60L)
		usr->spc90 += blks;
	if (today - act > 60L * 24L * 60L * 60L)
		usr->spc60 += blks;
	if (today - act > 30L * 24L * 60L * 60L)
		usr->spc30 += blks;
}