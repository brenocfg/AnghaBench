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
struct hostent_data {int stayopen; scalar_t__ hostf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_HOSTS ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 

void
_sethosthtent(int f, struct hostent_data *hed)
{
	if (!hed->hostf)
		hed->hostf = fopen(_PATH_HOSTS, "re");
	else
		rewind(hed->hostf);
	hed->stayopen = f;
}