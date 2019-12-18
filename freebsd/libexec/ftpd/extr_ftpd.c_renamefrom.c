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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ guest ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ noguestmod ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*) ; 

char *
renamefrom(char *name)
{
	struct stat st;

	if (guest && noguestmod) {
		reply(550, "Operation not permitted.");
		return (NULL);
	}
	if (lstat(name, &st) < 0) {
		perror_reply(550, name);
		return (NULL);
	}
	reply(350, "File exists, ready for destination name.");
	return (name);
}