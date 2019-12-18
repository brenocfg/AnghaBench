#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int status; } ;
struct TYPE_9__ {int status; int error; int lba_low; int lba_mid; int lba_high; int device; int lba_low_exp; int lba_mid_exp; int lba_high_exp; int sector_count; int sector_count_exp; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  command; } ;
struct TYPE_12__ {int dxfer_len; int resid; TYPE_3__ res; TYPE_2__ cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  cdb_bytes; } ;
struct TYPE_11__ {int dxfer_len; int resid; TYPE_1__ cdb_io; } ;
union ccb {TYPE_4__ ccb_h; TYPE_6__ ataio; TYPE_5__ csio; } ;
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct get_hook {char** argv; int /*<<< orphan*/  got; int /*<<< orphan*/  argc; } ;
struct cam_device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  cdb ;
typedef  int /*<<< orphan*/  atacmd ;

/* Variables and functions */
 int CAM_ARG_CMD_IN ; 
 int CAM_ARG_CMD_OUT ; 
 int CAM_ARG_ERR_RECOVER ; 
 int CAM_ARG_VERBOSE ; 
 int /*<<< orphan*/  CAM_ATAIO_DMA ; 
 int /*<<< orphan*/  CAM_ATAIO_FPDMA ; 
 int /*<<< orphan*/  CAM_ATAIO_NEEDRESULT ; 
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int /*<<< orphan*/  CAM_PASS_ERR_RECOVER ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (union ccb*) ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  arg_put ; 
 int arglist ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  buff_decode_visit (int*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int buff_encode_visit (int*,int,char*,int /*<<< orphan*/ ,struct get_hook*) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_fill_ataio (TYPE_6__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  cam_fill_csio (TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int cam_send_ccb (struct cam_device*,union ccb*) ; 
 char* cget (struct get_hook*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  iget ; 
 int /*<<< orphan*/  isspace (char) ; 
 scalar_t__ malloc (int) ; 
 char* optarg ; 
 int /*<<< orphan*/  optind ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char const*) ; 
 int /*<<< orphan*/  warnx (char const*,...) ; 
 int write (int,int*,int) ; 

__attribute__((used)) static int
scsicmd(struct cam_device *device, int argc, char **argv, char *combinedopt,
	int task_attr, int retry_count, int timeout)
{
	union ccb *ccb;
	u_int32_t flags = CAM_DIR_NONE;
	u_int8_t *data_ptr = NULL;
	u_int8_t cdb[20];
	u_int8_t atacmd[12];
	struct get_hook hook;
	int c, data_bytes = 0, valid_bytes;
	int cdb_len = 0;
	int atacmd_len = 0;
	int dmacmd = 0;
	int fpdmacmd = 0;
	int need_res = 0;
	char *datastr = NULL, *tstr, *resstr = NULL;
	int error = 0;
	int fd_data = 0, fd_res = 0;
	int retval;

	ccb = cam_getccb(device);

	if (ccb == NULL) {
		warnx("scsicmd: error allocating ccb");
		return (1);
	}

	CCB_CLEAR_ALL_EXCEPT_HDR(ccb);

	while ((c = getopt(argc, argv, combinedopt)) != -1) {
		switch(c) {
		case 'a':
			tstr = optarg;
			while (isspace(*tstr) && (*tstr != '\0'))
				tstr++;
			hook.argc = argc - optind;
			hook.argv = argv + optind;
			hook.got = 0;
			atacmd_len = buff_encode_visit(atacmd, sizeof(atacmd), tstr,
						    iget, &hook);
			/*
			 * Increment optind by the number of arguments the
			 * encoding routine processed.  After each call to
			 * getopt(3), optind points to the argument that
			 * getopt should process _next_.  In this case,
			 * that means it points to the first command string
			 * argument, if there is one.  Once we increment
			 * this, it should point to either the next command
			 * line argument, or it should be past the end of
			 * the list.
			 */
			optind += hook.got;
			break;
		case 'c':
			tstr = optarg;
			while (isspace(*tstr) && (*tstr != '\0'))
				tstr++;
			hook.argc = argc - optind;
			hook.argv = argv + optind;
			hook.got = 0;
			cdb_len = buff_encode_visit(cdb, sizeof(cdb), tstr,
						    iget, &hook);
			/*
			 * Increment optind by the number of arguments the
			 * encoding routine processed.  After each call to
			 * getopt(3), optind points to the argument that
			 * getopt should process _next_.  In this case,
			 * that means it points to the first command string
			 * argument, if there is one.  Once we increment
			 * this, it should point to either the next command
			 * line argument, or it should be past the end of
			 * the list.
			 */
			optind += hook.got;
			break;
		case 'd':
			dmacmd = 1;
			break;
		case 'f':
			fpdmacmd = 1;
			break;
		case 'i':
			if (arglist & CAM_ARG_CMD_OUT) {
				warnx("command must either be "
				      "read or write, not both");
				error = 1;
				goto scsicmd_bailout;
			}
			arglist |= CAM_ARG_CMD_IN;
			flags = CAM_DIR_IN;
			data_bytes = strtol(optarg, NULL, 0);
			if (data_bytes <= 0) {
				warnx("invalid number of input bytes %d",
				      data_bytes);
				error = 1;
				goto scsicmd_bailout;
			}
			hook.argc = argc - optind;
			hook.argv = argv + optind;
			hook.got = 0;
			optind++;
			datastr = cget(&hook, NULL);
			/*
			 * If the user supplied "-" instead of a format, he
			 * wants the data to be written to stdout.
			 */
			if ((datastr != NULL)
			 && (datastr[0] == '-'))
				fd_data = 1;

			data_ptr = (u_int8_t *)malloc(data_bytes);
			if (data_ptr == NULL) {
				warnx("can't malloc memory for data_ptr");
				error = 1;
				goto scsicmd_bailout;
			}
			break;
		case 'o':
			if (arglist & CAM_ARG_CMD_IN) {
				warnx("command must either be "
				      "read or write, not both");
				error = 1;
				goto scsicmd_bailout;
			}
			arglist |= CAM_ARG_CMD_OUT;
			flags = CAM_DIR_OUT;
			data_bytes = strtol(optarg, NULL, 0);
			if (data_bytes <= 0) {
				warnx("invalid number of output bytes %d",
				      data_bytes);
				error = 1;
				goto scsicmd_bailout;
			}
			hook.argc = argc - optind;
			hook.argv = argv + optind;
			hook.got = 0;
			datastr = cget(&hook, NULL);
			data_ptr = (u_int8_t *)malloc(data_bytes);
			if (data_ptr == NULL) {
				warnx("can't malloc memory for data_ptr");
				error = 1;
				goto scsicmd_bailout;
			}
			bzero(data_ptr, data_bytes);
			/*
			 * If the user supplied "-" instead of a format, he
			 * wants the data to be read from stdin.
			 */
			if ((datastr != NULL)
			 && (datastr[0] == '-'))
				fd_data = 1;
			else
				buff_encode_visit(data_ptr, data_bytes, datastr,
						  iget, &hook);
			optind += hook.got;
			break;
		case 'r':
			need_res = 1;
			hook.argc = argc - optind;
			hook.argv = argv + optind;
			hook.got = 0;
			resstr = cget(&hook, NULL);
			if ((resstr != NULL) && (resstr[0] == '-'))
				fd_res = 1;
			optind += hook.got;
			break;
		default:
			break;
		}
	}

	/*
	 * If fd_data is set, and we're writing to the device, we need to
	 * read the data the user wants written from stdin.
	 */
	if ((fd_data == 1) && (arglist & CAM_ARG_CMD_OUT)) {
		ssize_t amt_read;
		int amt_to_read = data_bytes;
		u_int8_t *buf_ptr = data_ptr;

		for (amt_read = 0; amt_to_read > 0;
		     amt_read = read(STDIN_FILENO, buf_ptr, amt_to_read)) {
			if (amt_read == -1) {
				warn("error reading data from stdin");
				error = 1;
				goto scsicmd_bailout;
			}
			amt_to_read -= amt_read;
			buf_ptr += amt_read;
		}
	}

	if (arglist & CAM_ARG_ERR_RECOVER)
		flags |= CAM_PASS_ERR_RECOVER;

	/* Disable freezing the device queue */
	flags |= CAM_DEV_QFRZDIS;

	if (cdb_len) {
		/*
		 * This is taken from the SCSI-3 draft spec.
		 * (T10/1157D revision 0.3)
		 * The top 3 bits of an opcode are the group code.
		 * The next 5 bits are the command code.
		 * Group 0:  six byte commands
		 * Group 1:  ten byte commands
		 * Group 2:  ten byte commands
		 * Group 3:  reserved
		 * Group 4:  sixteen byte commands
		 * Group 5:  twelve byte commands
		 * Group 6:  vendor specific
		 * Group 7:  vendor specific
		 */
		switch((cdb[0] >> 5) & 0x7) {
			case 0:
				cdb_len = 6;
				break;
			case 1:
			case 2:
				cdb_len = 10;
				break;
			case 3:
			case 6:
			case 7:
				/* computed by buff_encode_visit */
				break;
			case 4:
				cdb_len = 16;
				break;
			case 5:
				cdb_len = 12;
				break;
		}

		/*
		 * We should probably use csio_build_visit or something like that
		 * here, but it's easier to encode arguments as you go.  The
		 * alternative would be skipping the CDB argument and then encoding
		 * it here, since we've got the data buffer argument by now.
		 */
		bcopy(cdb, &ccb->csio.cdb_io.cdb_bytes, cdb_len);

		cam_fill_csio(&ccb->csio,
		      /*retries*/ retry_count,
		      /*cbfcnp*/ NULL,
		      /*flags*/ flags,
		      /*tag_action*/ task_attr,
		      /*data_ptr*/ data_ptr,
		      /*dxfer_len*/ data_bytes,
		      /*sense_len*/ SSD_FULL_SIZE,
		      /*cdb_len*/ cdb_len,
		      /*timeout*/ timeout ? timeout : 5000);
	} else {
		atacmd_len = 12;
		bcopy(atacmd, &ccb->ataio.cmd.command, atacmd_len);
		if (need_res)
			ccb->ataio.cmd.flags |= CAM_ATAIO_NEEDRESULT;
		if (dmacmd)
			ccb->ataio.cmd.flags |= CAM_ATAIO_DMA;
		if (fpdmacmd)
			ccb->ataio.cmd.flags |= CAM_ATAIO_FPDMA;

		cam_fill_ataio(&ccb->ataio,
		      /*retries*/ retry_count,
		      /*cbfcnp*/ NULL,
		      /*flags*/ flags,
		      /*tag_action*/ 0,
		      /*data_ptr*/ data_ptr,
		      /*dxfer_len*/ data_bytes,
		      /*timeout*/ timeout ? timeout : 5000);
	}

	if (((retval = cam_send_ccb(device, ccb)) < 0)
	 || ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP)) {
		const char warnstr[] = "error sending command";

		if (retval < 0)
			warn(warnstr);
		else
			warnx(warnstr);

		if (arglist & CAM_ARG_VERBOSE) {
			cam_error_print(device, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);
		}

		error = 1;
		goto scsicmd_bailout;
	}

	if (atacmd_len && need_res) {
		if (fd_res == 0) {
			buff_decode_visit(&ccb->ataio.res.status, 11, resstr,
					  arg_put, NULL);
			fprintf(stdout, "\n");
		} else {
			fprintf(stdout,
			    "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
			    ccb->ataio.res.status,
			    ccb->ataio.res.error,
			    ccb->ataio.res.lba_low,
			    ccb->ataio.res.lba_mid,
			    ccb->ataio.res.lba_high,
			    ccb->ataio.res.device,
			    ccb->ataio.res.lba_low_exp,
			    ccb->ataio.res.lba_mid_exp,
			    ccb->ataio.res.lba_high_exp,
			    ccb->ataio.res.sector_count,
			    ccb->ataio.res.sector_count_exp);
			fflush(stdout);
		}
	}

	if (cdb_len)
		valid_bytes = ccb->csio.dxfer_len - ccb->csio.resid;
	else
		valid_bytes = ccb->ataio.dxfer_len - ccb->ataio.resid;
	if (((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_REQ_CMP)
	 && (arglist & CAM_ARG_CMD_IN)
	 && (valid_bytes > 0)) {
		if (fd_data == 0) {
			buff_decode_visit(data_ptr, valid_bytes, datastr,
					  arg_put, NULL);
			fprintf(stdout, "\n");
		} else {
			ssize_t amt_written;
			int amt_to_write = valid_bytes;
			u_int8_t *buf_ptr = data_ptr;

			for (amt_written = 0; (amt_to_write > 0) &&
			     (amt_written =write(1, buf_ptr,amt_to_write))> 0;){
				amt_to_write -= amt_written;
				buf_ptr += amt_written;
			}
			if (amt_written == -1) {
				warn("error writing data to stdout");
				error = 1;
				goto scsicmd_bailout;
			} else if ((amt_written == 0)
				&& (amt_to_write > 0)) {
				warnx("only wrote %u bytes out of %u",
				      valid_bytes - amt_to_write, valid_bytes);
			}
		}
	}

scsicmd_bailout:

	if ((data_bytes > 0) && (data_ptr != NULL))
		free(data_ptr);

	cam_freeccb(ccb);

	return (error);
}