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
struct osd {int dummy; } ;
struct example {int /*<<< orphan*/  est_out_count; int /*<<< orphan*/  est_in_count; } ;

/* Variables and functions */
 int HHOOK_TCP_EST_IN ; 
 int HHOOK_TCP_EST_OUT ; 

__attribute__((used)) static int
example_hook(int hhook_type, int hhook_id, void *udata, void *ctx_data,
    void *hdata, struct osd *hosd)
{
	struct example *data;

	data = hdata;

	if (hhook_id == HHOOK_TCP_EST_IN)
		data->est_in_count++;
	else if (hhook_id == HHOOK_TCP_EST_OUT)
		data->est_out_count++;

	return (0);
}