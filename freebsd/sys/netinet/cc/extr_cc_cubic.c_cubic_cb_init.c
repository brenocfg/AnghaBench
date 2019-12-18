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
struct cubic {int mean_rtt_ticks; int /*<<< orphan*/  min_rtt_ticks; int /*<<< orphan*/  t_last_cong; } ;
struct cc_var {struct cubic* cc_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_CUBIC ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TCPTV_SRTTBASE ; 
 struct cubic* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int
cubic_cb_init(struct cc_var *ccv)
{
	struct cubic *cubic_data;

	cubic_data = malloc(sizeof(struct cubic), M_CUBIC, M_NOWAIT|M_ZERO);

	if (cubic_data == NULL)
		return (ENOMEM);

	/* Init some key variables with sensible defaults. */
	cubic_data->t_last_cong = ticks;
	cubic_data->min_rtt_ticks = TCPTV_SRTTBASE;
	cubic_data->mean_rtt_ticks = 1;

	ccv->cc_data = cubic_data;

	return (0);
}