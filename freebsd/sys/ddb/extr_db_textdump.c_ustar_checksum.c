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
typedef  int u_int ;
typedef  int u_char ;
struct ustar_header {char* uh_sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
ustar_checksum(struct ustar_header *uhp)
{
	u_int sum;
	int i;

	for (i = 0; i < sizeof(uhp->uh_sum); i++)
		uhp->uh_sum[i] = ' ';
	sum = 0;
	for (i = 0; i < sizeof(*uhp); i++)
		sum += ((u_char *)uhp)[i];
	snprintf(uhp->uh_sum, sizeof(uhp->uh_sum), "%6o", sum);
}