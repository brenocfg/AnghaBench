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
struct TYPE_2__ {int compression_in_started; int /*<<< orphan*/  compression_in_stream; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
#define  Z_MEM_ERROR 129 
#define  Z_OK 128 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 int inflateInit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
start_compression_in(struct ssh *ssh)
{
	if (ssh->state->compression_in_started == 1)
		inflateEnd(&ssh->state->compression_in_stream);
	switch (inflateInit(&ssh->state->compression_in_stream)) {
	case Z_OK:
		ssh->state->compression_in_started = 1;
		break;
	case Z_MEM_ERROR:
		return SSH_ERR_ALLOC_FAIL;
	default:
		return SSH_ERR_INTERNAL_ERROR;
	}
	return 0;
}