#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n_args; TYPE_1__* args; } ;
struct TYPE_4__ {int argtype; int arg_val; } ;
typedef  TYPE_2__ CMD ;

/* Variables and functions */
 int /*<<< orphan*/  current_line_number ; 
 int dos_cyls ; 
 int dos_cylsecs ; 
 int dos_heads ; 
 int dos_sectors ; 
 int geom_processed ; 
 scalar_t__ part_processed ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
process_geometry(CMD *command)
{
    int		status = 1, i;

    while (1) {
	geom_processed = 1;
	    if (part_processed) {
	    warnx(
	"ERROR line %d: the geometry specification line must occur before\n\
    all partition specifications",
		    current_line_number);
	    status = 0;
	    break;
	}
	    if (command->n_args != 3) {
	    warnx("ERROR line %d: incorrect number of geometry args",
		    current_line_number);
	    status = 0;
	    break;
	}
	    dos_cyls = 0;
	    dos_heads = 0;
	    dos_sectors = 0;
	    for (i = 0; i < 3; ++i) {
		    switch (command->args[i].argtype) {
	    case 'c':
		dos_cyls = command->args[i].arg_val;
		break;
	    case 'h':
		dos_heads = command->args[i].arg_val;
		break;
	    case 's':
		dos_sectors = command->args[i].arg_val;
		break;
	    default:
		warnx(
		"ERROR line %d: unknown geometry arg type: '%c' (0x%02x)",
			current_line_number, command->args[i].argtype,
			command->args[i].argtype);
		status = 0;
		break;
	    }
	}
	if (status == 0)
	    break;

	dos_cylsecs = dos_heads * dos_sectors;

	/*
	 * Do sanity checks on parameter values
	 */
	    if (dos_cyls == 0) {
	    warnx("ERROR line %d: number of cylinders not specified",
		    current_line_number);
	    status = 0;
	}
	    if (dos_cyls > 1024) {
	    warnx(
	"WARNING line %d: number of cylinders (%d) may be out-of-range\n\
    (must be within 1-1024 for normal BIOS operation, unless the entire disk\n\
    is dedicated to FreeBSD)",
		    current_line_number, dos_cyls);
	}

	    if (dos_heads == 0) {
	    warnx("ERROR line %d: number of heads not specified",
		    current_line_number);
	    status = 0;
	    } else if (dos_heads > 256) {
	    warnx("ERROR line %d: number of heads must be within (1-256)",
		    current_line_number);
	    status = 0;
	}

	    if (dos_sectors == 0) {
	    warnx("ERROR line %d: number of sectors not specified",
		    current_line_number);
	    status = 0;
	    } else if (dos_sectors > 63) {
	    warnx("ERROR line %d: number of sectors must be within (1-63)",
		    current_line_number);
	    status = 0;
	}

	break;
    }
    return (status);
}