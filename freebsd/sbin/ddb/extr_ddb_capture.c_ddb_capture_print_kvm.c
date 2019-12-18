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
typedef  char* u_int ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  db_capture_bufoff ;
typedef  int /*<<< orphan*/  db_capture_buf ;

/* Variables and functions */
 int /*<<< orphan*/  X_DB_CAPTURE_BUF ; 
 int /*<<< orphan*/  X_DB_CAPTURE_BUFOFF ; 
 int /*<<< orphan*/  bzero (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kread (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kread_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int,int /*<<< orphan*/ ) ; 
 char* malloc (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
ddb_capture_print_kvm(kvm_t *kvm)
{
	u_int db_capture_bufoff;
	char *buffer, *db_capture_buf;

	if (kread_symbol(kvm, X_DB_CAPTURE_BUF, &db_capture_buf,
	    sizeof(db_capture_buf), 0) < 0)
		errx(-1, "kvm: unable to read db_capture_buf");

	if (kread_symbol(kvm, X_DB_CAPTURE_BUFOFF, &db_capture_bufoff,
	    sizeof(db_capture_bufoff), 0) < 0)
		errx(-1, "kvm: unable to read db_capture_bufoff");

	buffer = malloc(db_capture_bufoff + 1);
	if (buffer == NULL)
		err(-1, "malloc: db_capture_bufoff (%u)",
		    db_capture_bufoff);
	bzero(buffer, db_capture_bufoff + 1);

	if (kread(kvm, db_capture_buf, buffer, db_capture_bufoff, 0) < 0)
		errx(-1, "kvm: unable to read buffer");

	printf("%s\n", buffer);
	free(buffer);
}