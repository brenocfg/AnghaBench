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
struct transfer_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  finish_request (struct transfer_request*) ; 

__attribute__((used)) static void process_response(void *callback_data)
{
	struct transfer_request *request =
		(struct transfer_request *)callback_data;

	finish_request(request);
}