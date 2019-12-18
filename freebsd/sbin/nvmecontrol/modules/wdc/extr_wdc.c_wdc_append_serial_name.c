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
struct nvme_controller_data {int /*<<< orphan*/  sn; } ;

/* Variables and functions */
 int NVME_SERIAL_NUMBER_LENGTH ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_controller_data (int,struct nvme_controller_data*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
wdc_append_serial_name(int fd, char *buf, size_t len, const char *suffix)
{
	struct nvme_controller_data	cdata;
	char sn[NVME_SERIAL_NUMBER_LENGTH + 1];
	char *walker;

	len -= strlen(buf);
	buf += strlen(buf);
	read_controller_data(fd, &cdata);
	memcpy(sn, cdata.sn, NVME_SERIAL_NUMBER_LENGTH);
	walker = sn + NVME_SERIAL_NUMBER_LENGTH - 1;
	while (walker > sn && *walker == ' ')
		walker--;
	*++walker = '\0';
	snprintf(buf, len, "%s%s.bin", sn, suffix);
}