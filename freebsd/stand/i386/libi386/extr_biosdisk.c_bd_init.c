#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bd_unit; } ;
typedef  TYPE_1__ bdinfo_t ;
struct TYPE_8__ {char* dv_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_NUMDRIVES ; 
 scalar_t__ PTOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_add_dev (int) ; 
 int /*<<< orphan*/  bd_int13probe (TYPE_1__*) ; 
 int /*<<< orphan*/  bd_link ; 
 TYPE_4__ bioshd ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hdinfo ; 
 int /*<<< orphan*/  printf (char*,char,char*,int) ; 

__attribute__((used)) static int
bd_init(void)
{
	int base, unit;
	bdinfo_t *bd;

	base = 0x80;
	for (unit = 0; unit < *(unsigned char *)PTOV(BIOS_NUMDRIVES); unit++) {
		/*
		 * Check the BIOS equipment list for number of fixed disks.
		 */
		if ((bd = calloc(1, sizeof(*bd))) == NULL)
			break;
		bd->bd_unit = base + unit;
		if (!bd_int13probe(bd)) {
			free(bd);
			break;
		}

		printf("BIOS drive %c: is %s%d\n", ('C' + unit),
		    bioshd.dv_name, unit);

		STAILQ_INSERT_TAIL(&hdinfo, bd, bd_link);
	}
	bcache_add_dev(unit);
	return (0);
}