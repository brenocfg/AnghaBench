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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {scalar_t__ pfra_fback; } ;
struct pfr_astats {scalar_t__** pfras_bytes; scalar_t__** pfras_packets; TYPE_1__ pfras_a; int /*<<< orphan*/  pfras_tzero; } ;

/* Variables and functions */
 int PFR_DIR_MAX ; 
 scalar_t__ PFR_FB_NOCOUNT ; 
 int PFR_OP_ADDR_MAX ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_addrx (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char*** stats_text ; 

void
print_astats(struct pfr_astats *as, int dns)
{
	time_t	time = as->pfras_tzero;
	int	dir, op;

	print_addrx(&as->pfras_a, NULL, dns);
	printf("\tCleared:     %s", ctime(&time));
 	if (as->pfras_a.pfra_fback == PFR_FB_NOCOUNT)
		return;
	for (dir = 0; dir < PFR_DIR_MAX; dir++)
		for (op = 0; op < PFR_OP_ADDR_MAX; op++)
			printf("\t%-12s [ Packets: %-18llu Bytes: %-18llu ]\n",
			    stats_text[dir][op],
			    (unsigned long long)as->pfras_packets[dir][op],
			    (unsigned long long)as->pfras_bytes[dir][op]);
}