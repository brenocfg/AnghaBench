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
 int /*<<< orphan*/  UFS_EXTATTR_CMD_DISABLE ; 
 int /*<<< orphan*/  UFS_EXTATTR_CMD_ENABLE ; 
 int /*<<< orphan*/  UFS_EXTATTR_CMD_START ; 
 int /*<<< orphan*/  UFS_EXTATTR_CMD_STOP ; 
 int extattr_string_to_namespace (char*,int*) ; 
 int extattrctl (char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int initattr (int,char**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int showattr (int,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int	error = 0, attrnamespace;

	if (argc < 2)
		usage();

	if (!strcmp(argv[1], "start")) {
		if (argc != 3)
			usage();
		error = extattrctl(argv[2], UFS_EXTATTR_CMD_START, NULL, 0,
		    NULL);
		if (error) {
			perror("extattrctl start");
			return (-1);
		}
	} else if (!strcmp(argv[1], "stop")) {
		if (argc != 3)
			usage();
		error = extattrctl(argv[2], UFS_EXTATTR_CMD_STOP, NULL, 0,
		   NULL);
		if (error) {
			perror("extattrctl stop");
			return (-1);
		}
	} else if (!strcmp(argv[1], "enable")) {
		if (argc != 6)
			usage();
		error = extattr_string_to_namespace(argv[3], &attrnamespace);
		if (error) {
			perror("extattrctl enable");
			return (-1);
		}
		error = extattrctl(argv[2], UFS_EXTATTR_CMD_ENABLE, argv[5],
		    attrnamespace, argv[4]);
		if (error) {
			perror("extattrctl enable");
			return (-1);
		}
	} else if (!strcmp(argv[1], "disable")) {
		if (argc != 5)
			usage();
		error = extattr_string_to_namespace(argv[3], &attrnamespace);
		if (error) {
			perror("extattrctl disable");
			return (-1);
		}
		error = extattrctl(argv[2], UFS_EXTATTR_CMD_DISABLE, NULL,
		    attrnamespace, argv[4]);
		if (error) {
			perror("extattrctl disable");
			return (-1);
		}
	} else if (!strcmp(argv[1], "initattr")) {
		argc -= 2;
		argv += 2;
		error = initattr(argc, argv);
		if (error)
			return (-1);
	} else if (!strcmp(argv[1], "showattr")) {
		argc -= 2;
		argv += 2;
		error = showattr(argc, argv);
		if (error)
			return (-1);
	} else
		usage();

	return (0);
}