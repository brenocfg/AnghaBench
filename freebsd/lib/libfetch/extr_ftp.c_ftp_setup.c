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
struct ftpio {int dir; scalar_t__ err; scalar_t__ eof; int /*<<< orphan*/ * dconn; int /*<<< orphan*/ * cconn; } ;
typedef  int /*<<< orphan*/  conn_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ftpio*) ; 
 int /*<<< orphan*/  ftp_closefn ; 
 int /*<<< orphan*/  ftp_readfn ; 
 int /*<<< orphan*/  ftp_seekfn ; 
 int /*<<< orphan*/  ftp_writefn ; 
 int /*<<< orphan*/ * funopen (struct ftpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftpio* malloc (int) ; 

__attribute__((used)) static FILE *
ftp_setup(conn_t *cconn, conn_t *dconn, int mode)
{
	struct ftpio *io;
	FILE *f;

	if (cconn == NULL || dconn == NULL)
		return (NULL);
	if ((io = malloc(sizeof(*io))) == NULL)
		return (NULL);
	io->cconn = cconn;
	io->dconn = dconn;
	io->dir = mode;
	io->eof = io->err = 0;
	f = funopen(io, ftp_readfn, ftp_writefn, ftp_seekfn, ftp_closefn);
	if (f == NULL)
		free(io);
	return (f);
}