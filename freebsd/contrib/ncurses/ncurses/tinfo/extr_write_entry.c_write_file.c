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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  TERMTYPE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*) ; 
 scalar_t__ ERR ; 
 int MAX_ENTRY_SIZE ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ _nc_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_syserr_abort (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _nc_tic_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 unsigned int fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ write_object (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int) ; 

__attribute__((used)) static void
write_file(char *filename, TERMTYPE *tp)
{
    char buffer[MAX_ENTRY_SIZE];
    unsigned limit = sizeof(buffer);
    unsigned offset = 0;

    FILE *fp = (_nc_access(filename, W_OK) == 0) ? fopen(filename, "wb") : 0;
    if (fp == 0) {
	perror(filename);
	_nc_syserr_abort("can't open %s/%s", _nc_tic_dir(0), filename);
    }
    DEBUG(1, ("Created %s", filename));

    if (write_object(tp, buffer, &offset, limit) == ERR
	|| fwrite(buffer, sizeof(char), (size_t) offset, fp) != offset) {
	_nc_syserr_abort("error writing %s/%s", _nc_tic_dir(0), filename);
    }

    fclose(fp);
}