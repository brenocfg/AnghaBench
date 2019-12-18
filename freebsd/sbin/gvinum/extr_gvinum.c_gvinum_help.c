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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
gvinum_help(void)
{

	printf("COMMANDS\n"
	    "checkparity [-f] plex\n"
	    "        Check the parity blocks of a RAID-5 plex.\n"
	    "create [-f] description-file\n"
	    "        Create as per description-file or open editor.\n"
	    "attach plex volume [rename]\n"
	    "attach subdisk plex [offset] [rename]\n"
	    "        Attach a plex to a volume, or a subdisk to a plex\n"
	    "concat [-fv] [-n name] drives\n"
	    "        Create a concatenated volume from the specified drives.\n"
	    "detach [-f] [plex | subdisk]\n"
	    "        Detach a plex or a subdisk from the volume or plex to\n"
	    "        which it is attached.\n"
	    "grow plex drive\n"
	    "        Grow plex by creating a properly sized subdisk on drive\n"
	    "l | list [-r] [-v] [-V] [volume | plex | subdisk]\n"
	    "        List information about specified objects.\n"
	    "ld [-r] [-v] [-V] [volume]\n"
	    "        List information about drives.\n"
	    "ls [-r] [-v] [-V] [subdisk]\n"
	    "        List information about subdisks.\n"
	    "lp [-r] [-v] [-V] [plex]\n"
	    "        List information about plexes.\n"
	    "lv [-r] [-v] [-V] [volume]\n"
	    "        List information about volumes.\n"
	    "mirror [-fsv] [-n name] drives\n"
	    "        Create a mirrored volume from the specified drives.\n"
	    "move | mv -f drive object ...\n"
	    "        Move the object(s) to the specified drive.\n"
	    "quit    Exit the vinum program when running in interactive mode."
	    "  Nor-\n"
	    "        mally this would be done by entering the EOF character.\n"
	    "raid5 [-fv] [-s stripesize] [-n name] drives\n"
	    "        Create a RAID-5 volume from the specified drives.\n"
	    "rename [-r] [drive | subdisk | plex | volume] newname\n"
	    "        Change the name of the specified object.\n"
	    "rebuildparity plex [-f]\n"
	    "        Rebuild the parity blocks of a RAID-5 plex.\n"
	    "resetconfig [-f]\n"
	    "        Reset the complete gvinum configuration\n"
	    "rm [-r] [-f] volume | plex | subdisk | drive\n"
	    "        Remove an object.\n"
	    "saveconfig\n"
	    "        Save vinum configuration to disk after configuration"
	    " failures.\n"
	    "setstate [-f] state [volume | plex | subdisk | drive]\n"
	    "        Set state without influencing other objects, for"
	    " diagnostic pur-\n"
	    "        poses only.\n"
	    "start [-S size] volume | plex | subdisk\n"
	    "        Allow the system to access the objects.\n"
	    "stripe [-fv] [-n name] drives\n"
	    "        Create a striped volume from the specified drives.\n"
	);
}