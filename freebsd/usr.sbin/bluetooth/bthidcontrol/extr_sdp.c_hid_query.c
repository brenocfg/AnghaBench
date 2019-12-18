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
struct hid_device {int /*<<< orphan*/  bdaddr; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 int /*<<< orphan*/  OK ; 
 char* bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 scalar_t__ hid_sdp_query (int /*<<< orphan*/ *,struct hid_device*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_hid_device (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int) ; 

__attribute__((used)) static int32_t
hid_query(bdaddr_t *bdaddr, int argc, char **argv)
{
	struct hid_device	hd;
	int			e;

	memcpy(&hd.bdaddr, bdaddr, sizeof(hd.bdaddr));
	if (hid_sdp_query(NULL, &hd, &e) < 0) {
		fprintf(stderr, "Could not perform SDP query on the " \
			"device %s. %s (%d)\n", bt_ntoa(bdaddr, NULL),
			strerror(e), e);
		return (FAILED);
	}

	print_hid_device(&hd, stdout);

	return (OK);
}