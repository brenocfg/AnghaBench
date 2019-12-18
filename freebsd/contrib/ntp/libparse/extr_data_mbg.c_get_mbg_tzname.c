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
typedef  int /*<<< orphan*/  TZ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
get_mbg_tzname(
	unsigned char **buffpp,
	char *tznamep
	)
{
  strlcpy(tznamep, (char *)*buffpp, sizeof(TZ_NAME));
  *buffpp += sizeof(TZ_NAME);
}