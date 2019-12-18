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
struct inodesc {int id_fix; int /*<<< orphan*/  id_number; int /*<<< orphan*/  id_type; } ;

/* Variables and functions */
 int ALTERED ; 
 int /*<<< orphan*/  DATA ; 
#define  DONTKNOW 131 
 int /*<<< orphan*/  EEXIT ; 
#define  FIX 130 
#define  IGNORE 129 
#define  NOFIX 128 
 int /*<<< orphan*/  direrror (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  preen ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pwarn (char*,char const*) ; 
 int /*<<< orphan*/  reply (char*) ; 

int
dofix(struct inodesc *idesc, const char *msg)
{

	switch (idesc->id_fix) {

	case DONTKNOW:
		if (idesc->id_type == DATA)
			direrror(idesc->id_number, msg);
		else
			pwarn("%s", msg);
		if (preen) {
			printf(" (SALVAGED)\n");
			idesc->id_fix = FIX;
			return (ALTERED);
		}
		if (reply("SALVAGE") == 0) {
			idesc->id_fix = NOFIX;
			return (0);
		}
		idesc->id_fix = FIX;
		return (ALTERED);

	case FIX:
		return (ALTERED);

	case NOFIX:
	case IGNORE:
		return (0);

	default:
		errx(EEXIT, "UNKNOWN INODESC FIX MODE %d", idesc->id_fix);
	}
	/* NOTREACHED */
	return (0);
}