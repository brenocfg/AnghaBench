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
struct hostent {char* h_name; } ;
struct hid_device {int /*<<< orphan*/  bdaddr; scalar_t__ new_device; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int FAILED ; 
 int OK ; 
 struct hostent* bt_gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 char* bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_config () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 struct hid_device* get_next_hid_device (struct hid_device*) ; 
 scalar_t__ read_config_file () ; 
 scalar_t__ read_hids_file () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hid_known(bdaddr_t *bdaddr, int argc, char **argv)
{
	struct hid_device	*hd = NULL;
	struct hostent		*he = NULL;
	int			 e = FAILED;

	if (read_config_file() == 0) {
		if (read_hids_file() == 0) {
			e = OK;

			for (hd = get_next_hid_device(hd);
			     hd != NULL;
			     hd = get_next_hid_device(hd)) {
				if (hd->new_device)
					continue;

				he = bt_gethostbyaddr((char *) &hd->bdaddr,
						sizeof(hd->bdaddr),
						AF_BLUETOOTH);

				fprintf(stdout,
"%s %s\n",				bt_ntoa(&hd->bdaddr, NULL),
					(he != NULL && he->h_name != NULL)?
						he->h_name : "");
			}
		}

		clean_config();
	}

	return (e);
}