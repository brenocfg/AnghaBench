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
typedef  void* uint64_t ;
typedef  void* uint32_t ;
struct mprs_pass_thru {void* Timeout; int /*<<< orphan*/  DataDirection; void* DataSize; void* PtrData; void* DataOutSize; void* PtrDataOut; void* ReplySize; void* RequestSize; void* PtrReply; void* PtrRequest; } ;
typedef  int /*<<< orphan*/  pass ;

/* Variables and functions */
 int /*<<< orphan*/  MPR_PASS_THRU_DIRECTION_BOTH ; 
 int /*<<< orphan*/  MPR_PASS_THRU_DIRECTION_NONE ; 
 int /*<<< orphan*/  MPR_PASS_THRU_DIRECTION_READ ; 
 int /*<<< orphan*/  MPR_PASS_THRU_DIRECTION_WRITE ; 
 int /*<<< orphan*/  MPS_PASS_THRU_DIRECTION_BOTH ; 
 int /*<<< orphan*/  MPS_PASS_THRU_DIRECTION_NONE ; 
 int /*<<< orphan*/  MPS_PASS_THRU_DIRECTION_READ ; 
 int /*<<< orphan*/  MPS_PASS_THRU_DIRECTION_WRITE ; 
 int /*<<< orphan*/  MPTIOCTL_PASS_THRU ; 
 int /*<<< orphan*/  bzero (struct mprs_pass_thru*,int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mprs_pass_thru*) ; 
 scalar_t__ is_mps ; 

int
mps_pass_command(int fd, void *req, uint32_t req_len, void *reply,
	uint32_t reply_len, void *data_in, uint32_t datain_len, void *data_out,
	uint32_t dataout_len, uint32_t timeout)
{
	struct mprs_pass_thru pass;

	bzero(&pass, sizeof(pass));
	pass.PtrRequest = (uint64_t)(uintptr_t)req;
	pass.PtrReply = (uint64_t)(uintptr_t)reply;
	pass.RequestSize = req_len;
	pass.ReplySize = reply_len;
	if (datain_len && dataout_len) {
		pass.PtrData = (uint64_t)(uintptr_t)data_in;
		pass.PtrDataOut = (uint64_t)(uintptr_t)data_out;
		pass.DataSize = datain_len;
		pass.DataOutSize = dataout_len;
		if (is_mps) {
			pass.DataDirection = MPS_PASS_THRU_DIRECTION_BOTH;
		} else {
			pass.DataDirection = MPR_PASS_THRU_DIRECTION_BOTH;
		}
	} else if (datain_len) {
		pass.PtrData = (uint64_t)(uintptr_t)data_in;
		pass.DataSize = datain_len;
		if (is_mps) {
			pass.DataDirection = MPS_PASS_THRU_DIRECTION_READ;
		} else {
			pass.DataDirection = MPR_PASS_THRU_DIRECTION_READ;
		}
	} else if (dataout_len) {
		pass.PtrData = (uint64_t)(uintptr_t)data_out;
		pass.DataSize = dataout_len;
		if (is_mps) {
			pass.DataDirection = MPS_PASS_THRU_DIRECTION_WRITE;
		} else {
			pass.DataDirection = MPR_PASS_THRU_DIRECTION_WRITE;
		}
	} else {
		if (is_mps) {
			pass.DataDirection = MPS_PASS_THRU_DIRECTION_NONE;
		} else {
			pass.DataDirection = MPR_PASS_THRU_DIRECTION_NONE;
		}
	}
	pass.Timeout = timeout;

	if (ioctl(fd, MPTIOCTL_PASS_THRU, &pass) < 0)
		return (errno);
	return (0);
}