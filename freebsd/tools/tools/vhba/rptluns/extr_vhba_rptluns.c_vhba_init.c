#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int disk_size; int* rpbitmap; int /*<<< orphan*/  qt; int /*<<< orphan*/  disk; TYPE_2__* vhba; } ;
typedef  TYPE_1__ vhbarptluns_t ;
struct TYPE_6__ {TYPE_1__* private; } ;
typedef  TYPE_2__ vhba_softc_t ;
struct timeval {int tv_usec; } ;

/* Variables and functions */
 int DISK_SIZE ; 
 int MAX_LUN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int arc4random () ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vhba_task ; 

void
vhba_init(vhba_softc_t *vhba)
{
	static vhbarptluns_t vhbas;
	struct timeval now;
	int i;

	vhbas.vhba = vhba;
	vhbas.disk_size = DISK_SIZE << 20;
	vhbas.disk = malloc(vhbas.disk_size, M_DEVBUF, M_WAITOK|M_ZERO);
	vhba->private = &vhbas;
	printf("setting luns");
	getmicrotime(&now);
	if (now.tv_usec & 0x1) {
		vhbas.rpbitmap[0] |= 1;
	}
	for (i = 1; i < 8; i++) {
		if (arc4random() & 1) {
			printf(" %d", i);
			vhbas.rpbitmap[0] |= (1 << i);
		}
	}
	for (i = 8; i < MAX_LUN; i++) {
		if ((arc4random() % i) == 0) {
			vhbas.rpbitmap[i >> 3] |= (1 << (i & 0x7));
			printf(" %d", i);
		}
	}
	printf("\n");
	TASK_INIT(&vhbas.qt, 0, vhba_task, &vhbas);
}