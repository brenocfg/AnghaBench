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
typedef  int /*<<< orphan*/  u_char ;
struct g_part_table {int dummy; } ;
struct g_part_parms {scalar_t__ gpp_codesize; int /*<<< orphan*/ * gpp_codeptr; } ;
struct g_part_bsd_table {int bbarea; } ;

/* Variables and functions */
 scalar_t__ BBSIZE ; 
 scalar_t__ BOOT1_SIZE ; 
 int BOOT2_OFF ; 
 scalar_t__ BOOT2_SIZE ; 
 int ENODEV ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int,scalar_t__) ; 

__attribute__((used)) static int
g_part_bsd_bootcode(struct g_part_table *basetable, struct g_part_parms *gpp)
{
	struct g_part_bsd_table *table;
	const u_char *codeptr;

	if (gpp->gpp_codesize != BOOT1_SIZE && gpp->gpp_codesize != BBSIZE)
		return (ENODEV);

	table = (struct g_part_bsd_table *)basetable;
	codeptr = gpp->gpp_codeptr;
	bcopy(codeptr, table->bbarea, BOOT1_SIZE);
	if (gpp->gpp_codesize == BBSIZE)
		bcopy(codeptr + BOOT2_OFF, table->bbarea + BOOT2_OFF,
		    BOOT2_SIZE);
	return (0);
}