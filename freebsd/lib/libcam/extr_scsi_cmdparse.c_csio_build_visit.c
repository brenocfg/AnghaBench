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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SCSI_MAX_CDBLEN ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  bzero (struct ccb_scsiio*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int do_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int (*) (void*,char*),void*,char const*,int /*<<< orphan*/ *) ; 

int
csio_build_visit(struct ccb_scsiio *csio, u_int8_t *data_ptr,
		 u_int32_t dxfer_len, u_int32_t flags, int retry_count,
		 int timeout, const char *cmd_spec,
		 int (*arg_get)(void *hook, char *field_name), void *gethook)
{
	size_t cmdlen;
	int retval;

	if (csio == NULL)
		return (0);

	/*
	 * We need something to encode, but we can't get it without the
	 * arg_get function.
	 */
	if (arg_get == NULL)
		return (-1);

	bzero(csio, sizeof(struct ccb_scsiio));

	if ((retval = do_encode(csio->cdb_io.cdb_bytes, SCSI_MAX_CDBLEN,
				&cmdlen, arg_get, gethook, cmd_spec, NULL)) == -1)
		return (retval);

	cam_fill_csio(csio,
		      /* retries */ retry_count,
		      /* cbfcnp */ NULL,
		      /* flags */ flags,
		      /* tag_action */ MSG_SIMPLE_Q_TAG,
		      /* data_ptr */ data_ptr,
		      /* dxfer_len */ dxfer_len,
		      /* sense_len */ SSD_FULL_SIZE,
		      /* cdb_len */ cmdlen,
		      /* timeout */ timeout ? timeout : 5000);

	return (retval);
}