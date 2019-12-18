#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_2__ {int error; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 TYPE_1__* rp_errors ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

char *
rp_strerror(int error)
{
	static char s[100];
	size_t space = sizeof(s);
	int i = 0;

	while (rp_errors[i].desc != NULL) {
		if (rp_errors[i].error == error) {
			strlcpy(s, rp_errors[i].desc, space);
			space -= strlen(rp_errors[i].desc);
		}
		i++;
	}
	if (s[0] == '\0')
		sprintf(s, "unknown (error=%d)", error);
	return (s);
}