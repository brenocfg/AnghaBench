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
typedef  int u_int ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  db_capture_inprogress ;
typedef  int /*<<< orphan*/  db_capture_bufsize ;
typedef  int /*<<< orphan*/  db_capture_bufoff ;

/* Variables and functions */
 int /*<<< orphan*/  X_DB_CAPTURE_BUFOFF ; 
 int /*<<< orphan*/  X_DB_CAPTURE_BUFSIZE ; 
 int /*<<< orphan*/  X_DB_CAPTURE_INPROGRESS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ kread_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ddb_capture_status_kvm(kvm_t *kvm)
{
	u_int db_capture_bufoff, db_capture_bufsize, db_capture_inprogress;

	if (kread_symbol(kvm, X_DB_CAPTURE_BUFOFF, &db_capture_bufoff,
	    sizeof(db_capture_bufoff), 0) < 0)
		errx(-1, "kvm: unable to read db_capture_bufoff");
	if (kread_symbol(kvm, X_DB_CAPTURE_BUFSIZE, &db_capture_bufsize,
	    sizeof(db_capture_bufsize), 0) < 0)
		errx(-1, "kvm: unable to read db_capture_bufsize");
	if (kread_symbol(kvm, X_DB_CAPTURE_INPROGRESS,
	    &db_capture_inprogress, sizeof(db_capture_inprogress), 0) < 0)
		err(-1, "kvm: unable to read db_capture_inprogress");
	printf("%u/%u bytes used\n", db_capture_bufoff, db_capture_bufsize);
	if (db_capture_inprogress)
		printf("capture is on\n");
	else
		printf("capture is off\n");

}