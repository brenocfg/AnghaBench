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
struct spu_context {TYPE_1__* switch_log; } ;
struct TYPE_2__ {int head; int tail; } ;

/* Variables and functions */
 int SWITCH_LOG_BUFSIZE ; 

__attribute__((used)) static inline int spufs_switch_log_used(struct spu_context *ctx)
{
	return (ctx->switch_log->head - ctx->switch_log->tail) %
		SWITCH_LOG_BUFSIZE;
}