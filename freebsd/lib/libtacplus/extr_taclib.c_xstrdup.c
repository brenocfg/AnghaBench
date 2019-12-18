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
struct tac_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generr (struct tac_handle*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *
xstrdup(struct tac_handle *h, const char *s)
{
	char *r;

	if ((r = strdup(s)) == NULL)
		generr(h, "Out of memory");
	return r;
}