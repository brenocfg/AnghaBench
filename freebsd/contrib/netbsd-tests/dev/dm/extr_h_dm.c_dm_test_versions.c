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
struct plistref {int /*<<< orphan*/  pref_plist; } ;
typedef  int /*<<< orphan*/  prop_dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETBSD_DM_IOCTL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  __USE (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  prop_dictionary_create () ; 
 char* prop_dictionary_externalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_dictionary_externalize_to_pref (int /*<<< orphan*/ ,struct plistref*) ; 
 int /*<<< orphan*/  prop_dictionary_internalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_dictionary_internalize_from_file (char*) ; 
 int rump_init () ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_ioctl (int,int /*<<< orphan*/ ,struct plistref*) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dm_test_versions(void) {
	int fd;
	int error;
	prop_dictionary_t dict_in, dict_out;
	struct plistref prefp;
	char *xml;

	error = 0;
	
	error = rump_init();
	if (error != 0)
		err(1, "Rump init failed");
	
	fd = rump_sys_open("/dev/mapper/control", O_RDWR, 0);
	if (fd == -1)
		err(1, "Open dm device failed");

	dict_in  = prop_dictionary_internalize_from_file("dm_version_cmd.plist");
	dict_out = prop_dictionary_create();
	
	prop_dictionary_externalize_to_pref(dict_in, &prefp);
	
	error = rump_sys_ioctl(fd, NETBSD_DM_IOCTL, &prefp);
	if (error < 0)
		err(1, "Dm control ioctl failed");

	dict_out = prop_dictionary_internalize(prefp.pref_plist);
	
	xml = prop_dictionary_externalize(dict_out);
	__USE(xml);

	rump_sys_close(fd);

	return error;
}