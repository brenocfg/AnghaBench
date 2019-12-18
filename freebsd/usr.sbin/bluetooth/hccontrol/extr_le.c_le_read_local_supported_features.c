#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  rp ;
struct TYPE_2__ {int status; scalar_t__ le_features; } ;
typedef  TYPE_1__ ng_hci_le_read_local_supported_features_rp ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HCI_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES ; 
 int /*<<< orphan*/  NG_HCI_OGF_LE ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hci_simple_request (int,int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
le_read_local_supported_features(int s, int argc ,char *argv[])
{
	ng_hci_le_read_local_supported_features_rp rp;
	int e;
	int n = sizeof(rp);

	e = hci_simple_request(s,
			NG_HCI_OPCODE(NG_HCI_OGF_LE,
			NG_HCI_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES), 
			(void *)&rp, &n);

	printf("LOCAL SUPPORTED: %d %d %jx\n", e, rp.status,
	       (uintmax_t) rp.le_features);

	return 0;
}