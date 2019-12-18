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
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {int compression_out_started; int /*<<< orphan*/  compression_out_stream; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
#define  Z_MEM_ERROR 129 
#define  Z_OK 128 
 int /*<<< orphan*/  debug (char*,int) ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int deflateInit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
start_compression_out(struct ssh *ssh, int level)
{
	if (level < 1 || level > 9)
		return SSH_ERR_INVALID_ARGUMENT;
	debug("Enabling compression at level %d.", level);
	if (ssh->state->compression_out_started == 1)
		deflateEnd(&ssh->state->compression_out_stream);
	switch (deflateInit(&ssh->state->compression_out_stream, level)) {
	case Z_OK:
		ssh->state->compression_out_started = 1;
		break;
	case Z_MEM_ERROR:
		return SSH_ERR_ALLOC_FAIL;
	default:
		return SSH_ERR_INTERNAL_ERROR;
	}
	return 0;
}