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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 char* sbuf_data (struct sbuf*) ; 
 int sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_cdb_sbuf (int /*<<< orphan*/ *,struct sbuf*) ; 

char *
scsi_cdb_string(u_int8_t *cdb_ptr, char *cdb_string, size_t len)
{
	struct sbuf sb;
	int error;

	if (len == 0)
		return ("");

	sbuf_new(&sb, cdb_string, len, SBUF_FIXEDLEN);

	scsi_cdb_sbuf(cdb_ptr, &sb);

	/* ENOMEM just means that the fixed buffer is full, OK to ignore */
	error = sbuf_finish(&sb);
	if (error != 0 && error != ENOMEM)
		return ("");

	return(sbuf_data(&sb));
}